#include "mainview.h"
#include "math.h"
#include <numeric>

MainView::MainView(QWidget *parent) : QOpenGLWidget(parent) {
    qDebug() << "✓✓ MainView constructor";


    showCurvePts = false;
    showNet = true;
    updateUniformsRequired = true;
    selectedPt = -1;
    combs = false;
    steps = 1;
}

MainView::~MainView() {
    qDebug() << "✗✗ MainView destructor";
    debugLogger->stopLogging();
    clearArrays();

    glDeleteBuffers(1, &netCoordsBO);
    glDeleteBuffers(1, &interpolatedCoordsBO);
    glDeleteVertexArrays(1, &netVAO);
    glDeleteVertexArrays(1, &interpolatedVAO);

    delete mainShaderProg;
    delete debugLogger;
}

// ---

void MainView::createShaderPrograms() {

    // Qt approach
    mainShaderProg = new QOpenGLShaderProgram();
    mainShaderProg->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertshader.glsl");
    mainShaderProg->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragshader.glsl");
    mainShaderProg->link();

    curveShaderProg = new QOpenGLShaderProgram();
    curveShaderProg->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertshader.glsl");
    curveShaderProg->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragshader.glsl");
    curveShaderProg->addShaderFromSourceFile(QOpenGLShader::Geometry, ":/shaders/geoshader.glsl");
    curveShaderProg->link();


    //  uni... = glGetUniformLocation(mainShaderProg->programId(), "...");
}

void MainView::createBuffers() {

    // Pure OpenGL
    glGenVertexArrays(1, &netVAO);
    glBindVertexArray(netVAO);

    glGenBuffers(1, &netCoordsBO);
    glBindBuffer(GL_ARRAY_BUFFER, netCoordsBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glGenVertexArrays(1, &interpolatedVAO);
    glBindVertexArray(interpolatedVAO);

    glGenBuffers(1, &interpolatedCoordsBO);
    glBindBuffer(GL_ARRAY_BUFFER, interpolatedCoordsBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
}

void MainView::updateBuffers() {
    QVector<QVector2D> interpolatedCoords = netCoords;
    for (int i = 0; i < steps; i++) {
        interpolatedCoords = generateCurvePoints(interpolatedCoords);
    }
    interpolatedCoordsADJ = linesToAdjacentLines(interpolatedCoords);

    glBindBuffer(GL_ARRAY_BUFFER, netCoordsBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D)*netCoords.size(), netCoords.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, interpolatedCoordsBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D)*interpolatedCoordsADJ.size(), interpolatedCoordsADJ.data(), GL_DYNAMIC_DRAW);

    update();

}

void MainView::updateUniforms() {

    //  glUniform...();
    curveShaderProg->setUniformValue("combs", combs);
    curveShaderProg->setUniformValue("circle", true);
    curveShaderProg->setUniformValue("selected_circle", 1);
    updateUniformsRequired = true;
}

void MainView::clearArrays() {

    // As of Qt 5.6, clear() does not release the memory anymore. Use e.g. squeeze()
    netCoords.clear();
    netCoords.squeeze();
    interpolatedCoords.clear();
    interpolatedCoords.squeeze();
}

// ---

void MainView::initializeGL() {

    initializeOpenGLFunctions();
    qDebug() << ":: OpenGL initialized";

    debugLogger = new QOpenGLDebugLogger();
    connect( debugLogger, SIGNAL( messageLogged( QOpenGLDebugMessage ) ), this, SLOT( onMessageLogged( QOpenGLDebugMessage ) ), Qt::DirectConnection );

    if ( debugLogger->initialize() ) {
        qDebug() << ":: Logging initialized";
        debugLogger->startLogging( QOpenGLDebugLogger::SynchronousLogging );
        debugLogger->enableMessages();
    }

    // If the application crashes here, try setting "MESA_GL_VERSION_OVERRIDE = 4.1"
    // and "MESA_GLSL_VERSION_OVERRIDE = 410" in Projects (left panel) -> Build Environment

    QString glVersion;
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    qDebug() << ":: Using OpenGL" << qPrintable(glVersion);

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);
    // Default is GL_LESS
    glDepthFunc(GL_LEQUAL);

    // ---

    createShaderPrograms();
    createBuffers();

    presetNet(0);
}

QVector<QVector2D> MainView::interpolateUsingMask(QVector<QVector2D> ctrlpoints, QVector<int> mask) {
    int len = ctrlpoints.size() - mask.size() + 1;
    int sum = std::accumulate(mask.begin(), mask.end(), 0);
    QVector<QVector2D> vs1 = QVector<QVector2D>(len);
    for (int i = 0; i < len; i++) {
        QVector2D v = QVector2D();
        for (int j = 0; j < mask.size(); j++) {
            v += (mask[j] * ctrlpoints[i + j] /  sum);
        }
        vs1[i] = v;
    }
    return vs1;
}

QVector<QVector2D> MainView::generateCurvePoints(QVector<QVector2D> ctrlpoints) {
    QVector<QVector2D> c1 = interpolateUsingMask(ctrlpoints, firstStencil);
    QVector<QVector2D> c2 = interpolateUsingMask(ctrlpoints, secondStencil);
    QVector<QVector2D> c = QVector<QVector2D>(c1.size() + c2.size());
    for(int i = 0; i < c1.size(); i++) {
        c[2*i] = c1[i];
    }
    for(int i = 0; i < c2.size(); i++) {
        c[2*i+1] = c2[i];
    }
    return c;
}

QVector<QVector2D> MainView::linesToAdjacentLines(QVector<QVector2D> lines) {
    QVector<QVector2D> r = QVector<QVector2D>();
    r.append(lines.last());
    r.append(lines.first());
    r.append(lines[1]);
    r.append(lines[2]);
    for (int i = 0; i < lines.size() - 3; i++) {
        r.append(lines[i]);
        r.append(lines[i+1]);
        r.append(lines[i+2]);
        r.append(lines[i+3]);
    }
    r.append(lines[lines.size()-3]);
    r.append(lines[lines.size()-2]);
    r.append(lines.last());
    r.append(lines.first());
    return r;
}

void MainView::paintGL() {

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mainShaderProg->bind();

    if (updateUniformsRequired) {
        updateUniforms();
    }

    if (showNet) {
        glBindVertexArray(netVAO);

        // Draw control net
        glDrawArrays(GL_LINE_STRIP, 0, netCoords.size());
        glPointSize(8.0);
        glDrawArrays(GL_POINTS, 0, netCoords.size());

        // Highlight selected control point
        if (selectedPt > -1) {
            glPointSize(12.0);
            glDrawArrays(GL_POINTS, selectedPt, 1);
        }

        glBindVertexArray(0);
    }
    mainShaderProg->release();
    curveShaderProg->bind();

    if (showCurvePts) {
        glBindVertexArray(interpolatedVAO);
        glDrawArrays(GL_LINES_ADJACENCY, 0, interpolatedCoordsADJ.size());
        glBindVertexArray(0);
    }

    curveShaderProg->release();
}

// ---

void MainView::presetNet(int preset) {
    selectedPt = -1;
    clearArrays();

    switch (preset) {
    case 0:
        // 'Pentagon'
        netCoords.reserve(5);
        netCoords.append(QVector2D(-0.25, -0.5));
        netCoords.append(QVector2D(-0.75, 0.0));
        netCoords.append(QVector2D(-0.25, 0.75));
        netCoords.append(QVector2D(0.75, 0.5));
        netCoords.append(QVector2D(0.5, -0.75));
        break;
    case 1:
        // 'Basis'
        netCoords.reserve(9);
        netCoords.append(QVector2D(-1.0, -0.25));
        netCoords.append(QVector2D(-0.75, -0.25));
        netCoords.append(QVector2D(-0.5, -0.25));
        netCoords.append(QVector2D(-0.25, -0.25));
        netCoords.append(QVector2D(0.0, 0.50));
        netCoords.append(QVector2D(0.25, -0.25));
        netCoords.append(QVector2D(0.5, -0.25));
        netCoords.append(QVector2D(0.75, -0.25));
        netCoords.append(QVector2D(1.0, -0.25));
        break;
    }

    updateBuffers();

}

void MainView::setMask(QString stringMask) {
    subdivMask.clear();

    QString trimmedMask;
    trimmedMask = stringMask.trimmed();

    // Convert to sequence of integers
    QTextStream intSeq(&trimmedMask);
    while (!intSeq.atEnd()) {
        int k;
        intSeq >> k;
        subdivMask.append(k);
    }

    // Stencils represent affine combinations (i.e. they should sum to unity)
    normalizeValue = 0;

    firstStencil.clear();
    secondStencil.clear();

    for (int k = 0; k < subdivMask.size(); ++k) {
        if (k % 2) {
            normalizeValue += subdivMask[k];
            firstStencil.append(subdivMask[k]);
        }
        else {
            secondStencil.append(subdivMask[k]);
        }
    }

    qDebug() << ":: Extracted stencils" << firstStencil << "and" << secondStencil;
}

// ---

void MainView::mousePressEvent(QMouseEvent *event) {
    // In order to allow keyPressEvents:
    setFocus();

    float xRatio, yRatio, xScene, yScene;

    xRatio = float(event->x()) / float(width());
    yRatio = float(event->y()) / float(height());

    // By default, the drawing canvas is the square [-1,1]^2:
    xScene = (1-xRatio)*-1 + xRatio*1;
    // Note that the origin of the canvas is in the top left corner (not the lower left).
    yScene = yRatio*-1 + (1-yRatio)*1;

    switch (event->buttons()) {
    case Qt::LeftButton:
        if (selectedPt > -1) {
            // De-select control point
            selectedPt = -1;
            setMouseTracking(false);
            update();
        } else {
            // Add new control point
            netCoords.append(QVector2D(xScene, yScene));
            updateBuffers();
        }
        break;
    case Qt::RightButton:
        // Select control point
        selectedPt = findClosest(xScene, yScene);
        update();
        break;
    }

}

void MainView::mouseMoveEvent(QMouseEvent *event) {
    if (selectedPt > -1) {
        float xRatio, yRatio, xScene, yScene;

        xRatio = float(event->x()) / float(width());
        yRatio = float(event->y()) / float(height());

        xScene = (1-xRatio)*-1 + xRatio*1;
        yScene = yRatio*-1 + (1-yRatio)*1;

        // Update position of the control point
        netCoords[selectedPt] = QVector2D(xScene, yScene);
        updateBuffers();
    }
}

void MainView::setCombs(int c) {
    if (c == 2) {
        combs = true;
    } else {
        combs = false;
    }
    updateUniformsRequired = true;
    updateBuffers();
    update();
}

void MainView::setSteps(int s) {
    steps = s;
    updateBuffers();
    update();
}

void MainView::setSelectedCircle(int s) {
    selected_circle = s;
    qDebug() << s;
    updateBuffers();
    update();
}

void MainView::keyPressEvent(QKeyEvent *event) {

    // Only works when the widget has focus!

    switch(event->key()) {
    case 'G':
        if (selectedPt > -1) {
            // Grab selected control point
            setMouseTracking(true);
        }
        break;
    case 'X':
        if (selectedPt > -1) {
            // Remove selected control point
            netCoords.remove(selectedPt);
            selectedPt = -1;
            updateBuffers();
        }
        break;
    }

}

int MainView::findClosest(float x, float y) {
    int ptIndex = -1;
    float currentDist, minDist = 4;
    QVector2D p = QVector2D(x, y);

    for (int k = 0; k < netCoords.size(); k++) {
        currentDist = netCoords[k].distanceToPoint(p);
        if (currentDist < minDist) {
            minDist = currentDist;
            ptIndex = k;
        }
    }

    return ptIndex;
}

// ---

void MainView::onMessageLogged( QOpenGLDebugMessage Message ) {
    qDebug() << " → Log:" << Message;
}
