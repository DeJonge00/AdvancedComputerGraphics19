#include "mainview.h"

MainView::MainView(QWidget *Parent) : QOpenGLWidget(Parent) {
    qDebug() << "✓✓ MainView constructor";

    modelLoaded = false;
    wireframeMode = true;
    uniformUpdateRequired = true;
    positionModeLimit = false;
    tessellation = 0;

    rotAngle = 0.0;
    FoV = 60.0;
}

MainView::~MainView() {
    qDebug() << "✗✗ MainView destructor";

    glDeleteBuffers(1, &meshCoordsBO);
    glDeleteBuffers(1, &meshNormalsBO);
    glDeleteBuffers(1, &meshIndexBO);
    glDeleteVertexArrays(1, &meshVAO);

    makeCurrent();
    debugLogger->stopLogging();

    delete debugLogger;
    delete mainShaderProg;
}

// ---

void MainView::createShaderPrograms() {
    qDebug() << ".. createShaderPrograms";

    mainShaderProg = new QOpenGLShaderProgram();
    mainShaderProg->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertshader.glsl");
    mainShaderProg->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragshader.glsl");

    mainShaderProg->link();

    tessShaderProg = new QOpenGLShaderProgram();
    tessShaderProg->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertshader.glsl");
    tessShaderProg->addShaderFromSourceFile(QOpenGLShader::TessellationControl, ":/shaders/tcs.glsl");
    tessShaderProg->addShaderFromSourceFile(QOpenGLShader::TessellationEvaluation, ":/shaders/tes.glsl");
    tessShaderProg->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragshader.glsl");

    tessShaderProg->link();
    setMatrices();
}

void MainView::setMatrices() {
    if (tessellation > 0) {
        uniModelViewMatrix = glGetUniformLocation(tessShaderProg->programId(), "modelviewmatrix");
        uniProjectionMatrix = glGetUniformLocation(tessShaderProg->programId(), "projectionmatrix");
        uniNormalMatrix = glGetUniformLocation(tessShaderProg->programId(), "normalmatrix");
    } else {
        uniModelViewMatrix = glGetUniformLocation(mainShaderProg->programId(), "modelviewmatrix");
        uniProjectionMatrix = glGetUniformLocation(mainShaderProg->programId(), "projectionmatrix");
        uniNormalMatrix = glGetUniformLocation(mainShaderProg->programId(), "normalmatrix");
    }
}

void MainView::createBuffers() {

    qDebug() << ".. createBuffers";

    glGenVertexArrays(1, &meshVAO);
    glBindVertexArray(meshVAO);

    glGenBuffers(1, &meshCoordsBO);
    glBindBuffer(GL_ARRAY_BUFFER, meshCoordsBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glGenBuffers(1, &meshNormalsBO);
    glBindBuffer(GL_ARRAY_BUFFER, meshNormalsBO);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glGenBuffers(1, &meshIndexBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshIndexBO);

    glBindVertexArray(0);
}

void MainView::updateMeshBuffers(Mesh& currentMesh) {

    qDebug() << ".. updateBuffers";

    //gather attributes for current mesh
    currentMesh.extractAttributes();
    QVector<QVector3D>& vertexCoords = currentMesh.getVertexCoords();
    if (positionModeLimit) {
        vertexCoords = currentMesh.getLimitPositions();
    }
    QVector<QVector3D>& vertexNormals = currentMesh.getVertexNorms();
    QVector<unsigned int>& polyIndices = currentMesh.getPolyIndices();
    if (tessellation > 0) {
        polyIndices = currentMesh.getPatches();
    }

    glBindBuffer(GL_ARRAY_BUFFER, meshCoordsBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D)*vertexCoords.size(), vertexCoords.data(), GL_DYNAMIC_DRAW);

    qDebug() << " → Updated meshCoordsBO";

    glBindBuffer(GL_ARRAY_BUFFER, meshNormalsBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D)*vertexNormals.size(), vertexNormals.data(), GL_DYNAMIC_DRAW);

    qDebug() << " → Updated meshNormalsBO";

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshIndexBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*polyIndices.size(), polyIndices.data(), GL_DYNAMIC_DRAW);

    qDebug() << " → Updated meshIndexBO";

    meshIBOSize = polyIndices.size();

    update();

}

void MainView::updateMatrices() {

    modelViewMatrix.setToIdentity();
    modelViewMatrix.translate(QVector3D(0.0, 0.0, -3.0));
    modelViewMatrix.scale(QVector3D(1.0, 1.0, 1.0));
    modelViewMatrix.rotate(rotAngle, QVector3D(0.0, 1.0, 0.0));

    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(FoV, dispRatio, 0.2, 4.0);

    normalMatrix = modelViewMatrix.normalMatrix();

    uniformUpdateRequired = true;
    update();

}

void MainView::updateUniforms(QOpenGLShaderProgram* shaderProg) {

    // mainShaderProg should be bound at this point!

    glUniformMatrix4fv(uniModelViewMatrix, 1, false, modelViewMatrix.data());
    glUniformMatrix4fv(uniProjectionMatrix, 1, false, projectionMatrix.data());
    glUniformMatrix3fv(uniNormalMatrix, 1, false, normalMatrix.data());
    shaderProg->setUniformValue("tessellation", tessellation);
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

    QString glVersion;
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    qDebug() << ":: Using OpenGL" << qPrintable(glVersion);

    makeCurrent();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);
    // Default is GL_LESS
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(MAX_INT);
    glPatchParameteri(GL_PATCH_VERTICES, 4);

    // ---

    createShaderPrograms();
    createBuffers();

    // ---


    updateMatrices();
}

void MainView::resizeGL(int newWidth, int newHeight) {

    qDebug() << ".. resizeGL";

    dispRatio = (float)newWidth/newHeight;
    updateMatrices();

}

void MainView::paintGL() {

    if (modelLoaded) {

        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        QOpenGLShaderProgram* shaderProg = mainShaderProg;
        if (tessellation > 0) {
            shaderProg = tessShaderProg;
        }
        shaderProg->bind();

        if (uniformUpdateRequired) {
            updateUniforms(shaderProg);
            uniformUpdateRequired = false;
        }

        renderMesh();

        shaderProg->release();
    }
}

// ---

void MainView::renderMesh() {

    glBindVertexArray(meshVAO);

    if (wireframeMode) {
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        glDrawElements(GL_LINE_LOOP, meshIBOSize, GL_UNSIGNED_INT, 0);
    } else if (tessellation > 0) {
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        glDrawElements(GL_PATCHES, meshIBOSize, GL_UNSIGNED_INT, 0);
    } else {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        glDrawElements(GL_TRIANGLE_FAN, meshIBOSize, GL_UNSIGNED_INT, 0);
    }

    glBindVertexArray(0);

}

// ---

void MainView::mousePressEvent(QMouseEvent* event) {
    setFocus();
}

void MainView::wheelEvent(QWheelEvent* event) {
    FoV -= event->delta() / 60.0;
    updateMatrices();
}

void MainView::keyPressEvent(QKeyEvent* event) {
    switch(event->key()) {
    case 'Z':
        wireframeMode = !wireframeMode;
        update();
        break;
    }
}

// ---

void MainView::onMessageLogged( QOpenGLDebugMessage Message ) {
    qDebug() << " → Log:" << Message;
}
