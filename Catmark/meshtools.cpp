#include "mesh.h"

HalfEdge* vertOnBoundary(Vertex* currentVertex) {

    unsigned short n = currentVertex->val;
    HalfEdge* currentEdge = currentVertex->out;

    for (unsigned int k = 0; k < n; k++) {
        if (!currentEdge->polygon) {
            return currentEdge;
        }
        currentEdge = currentEdge->prev->twin;
    }

    return nullptr;
}

bool isRegularMeshVertex(Vertex v) {
    HalfEdge *start = v.out, *current = v.out;
    do {
        if (current->polygon->val != 4) { return false; }
        current = current->twin->next;
    } while (current != start);
    return true;
}

// Return average of all vertices of a face
QVector3D Mesh::calcFacePoint(HalfEdge* current) {
    HalfEdge* h = current;
    QVector3D f = QVector3D();
    do {
        f += current->target->coords;
        h = h->next;
    } while (h != current);
    f /= current->polygon->val;
    return f;
}

// Check whether all vertices of a face have valency 4
bool isRegularMeshFace(Face f) {
    if (f.val != 4) {
        return false;
    }
    HalfEdge *start = f.side, *current = f.side;
    do {
        if (current->target->val != 4) {
            return false;
        }
        current = current->next;
    } while (current != start);
    return true;
}

// Construct array of patches consisting of vertice coordinates
QVector<unsigned int> Mesh::getPatches() {
    QVector<unsigned int> patches = QVector<unsigned int>();

    for (int i = 0; i < faces.size(); i++) {
        if (isRegularMeshFace(faces[i])) {
            HalfEdge* h = faces[i].side;
            for (int i = 0; i < faces[i].val; i++) {
                patches.append(h->target->index);
                h = h->next;
            }
        }
        polyIndices.append(MAX_INT);
    }
    return patches;
}

QVector<QVector3D> Mesh::getLimitPositions() {
//    qDebug() << "getLimitPositions start";
    QVector<QVector3D> vertexCoords = QVector<QVector3D>();
    // Calculate new position for each vertex
    for (int i = 0; i < vertices.size(); i++) {
        Vertex* currentVertex = &vertices[i];

        // Branch boundaries, regular meshpoints and other
        if (vertOnBoundary(currentVertex)) {
            vertexCoords.append(currentVertex->coords);
        } else if (isRegularMeshVertex(*currentVertex)) {
            vertexCoords.append(currentVertex->val*currentVertex->val * currentVertex->coords);
            HalfEdge *start = currentVertex->out, *current = currentVertex->out;
            do {
                // Add edgepoint e and (normalized) facepoint f with weights
                vertexCoords[i] += 4 * current->target->coords;
                vertexCoords[i] += calcFacePoint(current);

                // Loop index
                current = current->twin->next;
            } while (current != start);
            // Normalize
            vertexCoords[i] /= currentVertex->val * (currentVertex->val + 5);
        } else { // Irregular, non-boundary meshpoint == N-gon
            float n = currentVertex->val;
            QVector3D s = QVector3D();
            HalfEdge* current = currentVertex->out;
            do {
                s += ((current->target->coords + currentVertex->coords) / 2);
                s += calcFacePoint(current);
                // Loop index
                current = current->twin->next;
            } while (current != currentVertex->out);

            vertexCoords.append((n-3)/(n+5) * currentVertex->coords + (4 / (n*(n+5)) * s));
        }
    }
    qDebug() << "Retrieved Limit Positions";
    return vertexCoords;
}

void Mesh::subdivideCatmullClark(Mesh& mesh) {
    QVector<Vertex>& newVertices = mesh.getVertices();
    QVector<HalfEdge>& newHalfEdges = mesh.getHalfEdges();
    QVector<Face>& newFaces = mesh.getFaces();

    unsigned int numVerts, numHalfEdges, numFaces, sumFaceValences;
    unsigned int k, m, s, t;
    unsigned int vIndex, hIndex, fIndex;
    unsigned short n;
    HalfEdge* currentEdge;

    qDebug() << ":: Creating new Catmull-Clark mesh";

    numVerts = vertices.size();
    numHalfEdges = halfEdges.size();
    numFaces = faces.size();

    // Reserve memory
    newVertices.reserve(numFaces + numVerts + numHalfEdges/2);

    sumFaceValences = 0;
    for (k=0; k<numFaces; k++) {
        sumFaceValences += faces[k].val;
    }

    newHalfEdges.reserve(2*numHalfEdges + 2*sumFaceValences);
    newFaces.reserve(sumFaceValences);

    // Create face points
    for (k=0; k<numFaces; k++) {
        n = faces[k].val;
        // Coords (x,y,z), Out, Valence, Index
        newVertices.append( Vertex(facePoint(faces[k].side),
                                   nullptr,
                                   n,
                                   k) );
    }

    qDebug() << " * Created face points";

    vIndex = numFaces;

    // Create vertex points
    for (k=0; k<numVerts; k++) {
        n = vertices[k].val;
        // Coords (x,y,z), Out, Valence, Index
        newVertices.append( Vertex(vertexPoint(vertices[k].out, newVertices),
                                   nullptr,
                                   n,
                                   vIndex) );
        vIndex++;
    }

    qDebug() << " * Created vertex points";

    // Create edge points
    for (k=0; k<numHalfEdges; k++) {
        currentEdge = &halfEdges[k];

        if (k < currentEdge->twin->index) {
            m = (!currentEdge->polygon || !currentEdge->twin->polygon) ? 3 : 4;
            // Coords (x,y,z), Out, Valence, Index
            newVertices.append( Vertex(edgePoint(currentEdge, newVertices),
                                       nullptr,
                                       m,
                                       vIndex) );
            vIndex++;
        }
    }

    qDebug() << " * Created edge points";

    // Split halfedges
    splitHalfEdges(newVertices, newHalfEdges);

    qDebug() << " * Split halfedges";

    hIndex = 2*numHalfEdges;
    fIndex = 0;

    // Create faces and remaining halfedges
    for (k=0; k<numFaces; k++) {
        currentEdge = faces[k].side;
        n = faces[k].val;

        for (m=0; m<n; m++) {

            s = currentEdge->prev->index;
            t = currentEdge->index;

            // Side, Val, Index
            newFaces.append(Face(nullptr,
                                 4,
                                 fIndex));

            newFaces[fIndex].side = &newHalfEdges[ 2*t ];

            // Target, Next, Prev, Twin, Poly, Index
            newHalfEdges.append(HalfEdge( &newVertices[k],
                                          nullptr,
                                          &newHalfEdges[ 2*t ],
                                nullptr,
                                &newFaces[fIndex],
                                hIndex ));

            newHalfEdges.append(HalfEdge( nullptr,
                                          &newHalfEdges[2*s+1],
                                &newHalfEdges[hIndex],
                                nullptr,
                                &newFaces[fIndex],
                                hIndex+1 ));

            newHalfEdges[hIndex].next = &newHalfEdges[hIndex+1];
            newHalfEdges[hIndex+1].target = newHalfEdges[hIndex+1].next->twin->target;

            newHalfEdges[2*s+1].next = &newHalfEdges[2*t];
            newHalfEdges[2*s+1].prev = &newHalfEdges[hIndex+1];
            newHalfEdges[2*s+1].polygon = &newFaces[fIndex];

            newHalfEdges[2*t].next = &newHalfEdges[hIndex];
            newHalfEdges[2*t].prev = &newHalfEdges[2*s+1];
            newHalfEdges[2*t].polygon = &newFaces[fIndex];

            if (m > 0) {
                // Twins
                newHalfEdges[hIndex+1].twin = &newHalfEdges[hIndex-2];
                newHalfEdges[hIndex-2].twin = &newHalfEdges[hIndex+1];
            }

            // For edge points
            newHalfEdges[2*t].target->out = &newHalfEdges[hIndex];

            hIndex += 2;
            fIndex++;
            currentEdge = currentEdge->next;
        }

        newHalfEdges[hIndex-2*n+1].twin = &newHalfEdges[hIndex-2];
        newHalfEdges[hIndex-2].twin = &newHalfEdges[hIndex-2*n+1];

        // For face points
        newVertices[k].out = &newHalfEdges[hIndex-1];

    }

    qDebug() << " * Created faces and remaining halfedges";

    // For vertex points
    for (k=0; k<numVerts; k++) {
        newVertices[numFaces + k].out = &newHalfEdges[ 2*vertices[k].out->index ];
    }

    qDebug() << " * Completed!";
    qDebug() << "   # Vertices:" << newVertices.size();
    qDebug() << "   # HalfEdges:" << newHalfEdges.size();
    qDebug() << "   # Faces:" << newFaces.size();

}


// ---

QVector3D Mesh::vertexPoint(HalfEdge* firstEdge, QVector<Vertex>& newVertices) {
    unsigned short k;
    QVector3D sumStarPts, sumFacePts;
    QVector3D vertexPt;

    Vertex* currentVertex = firstEdge->twin->target;
    unsigned int n = currentVertex->val;

    sumStarPts = QVector3D();
    sumFacePts = QVector3D();
    HalfEdge* currentEdge = firstEdge;

    // Catmull-Clark (also supporting initial meshes containing n-gons)
    if (HalfEdge* boundaryEdge = vertOnBoundary(currentVertex)) {
        if (boundaryEdge->twin->target->val == 2) {
            // Interpolate corners
            vertexPt = boundaryEdge->twin->target->coords;
        }
        else {
            vertexPt  = 1.0 * boundaryEdge->target->coords;
            vertexPt += 6.0 * boundaryEdge->twin->target->coords;
            vertexPt += 1.0 * boundaryEdge->prev->twin->target->coords;
            vertexPt /= 8.0;
        }
    }
    else {
        for (k = 0; k < n; k++) {
            sumStarPts += currentEdge->target->coords;
            sumFacePts += newVertices[currentEdge->polygon->index].coords;
            currentEdge = currentEdge->prev->twin;
        }

        vertexPt = ((n-2)*currentVertex->coords + sumStarPts/n + sumFacePts/n)/n;
    }

    return vertexPt;

}

QVector3D Mesh::edgePoint(HalfEdge* firstEdge, QVector<Vertex>& newVertices) {
    QVector3D EdgePt = QVector3D();
    HalfEdge* currentEdge = firstEdge;

    // Catmull-Clark (also supporting initial meshes containing n-gons)
    if (!currentEdge->polygon || !currentEdge->twin->polygon) {
        EdgePt  = 4.0 * currentEdge->target->coords;
        EdgePt += 4.0 * currentEdge->twin->target->coords;
        EdgePt /= 8.0;
    }
    else {
        EdgePt  = currentEdge->target->coords;
        EdgePt += currentEdge->twin->target->coords;
        EdgePt += newVertices[currentEdge->polygon->index].coords;
        EdgePt += newVertices[currentEdge->twin->polygon->index].coords;
        EdgePt /= 4.0;
    }

    return EdgePt;

}

QVector3D Mesh::facePoint(HalfEdge* firstEdge) {
    QVector3D facePt;

    unsigned int n = firstEdge->polygon->val;
    facePt = QVector3D();
    HalfEdge* currentEdge = firstEdge;

    for (unsigned int k = 0; k < n; k++) {
        // General approach
        facePt += 1.0f/n * currentEdge->target->coords;
        currentEdge = currentEdge->next;
    }

    return facePt;

}


// For Bilinear, Catmull-Clark and Loop
void Mesh::splitHalfEdges(QVector<Vertex>& newVertices, QVector<HalfEdge>& newHalfEdges) {
    unsigned int k, m;
    unsigned int vIndex;
    HalfEdge* currentEdge;

    vIndex = vertices.size() + faces.size();

    for (k = 0; k < halfEdges.size(); k++) {
        currentEdge = &halfEdges[k];
        m = currentEdge->twin->index;

        // Target, Next, Prev, Twin, Poly, Index
        newHalfEdges.append(HalfEdge(nullptr,
                                     nullptr,
                                     nullptr,
                                     nullptr,
                                     nullptr,
                                     2*k));

        newHalfEdges.append(HalfEdge(nullptr,
                                     nullptr,
                                     nullptr,
                                     nullptr,
                                     nullptr,
                                     2*k+1));

        if (k < m) {
            newHalfEdges[2*k].target = &newVertices[ vIndex ];
            newHalfEdges[2*k+1].target = &newVertices[ faces.size() + currentEdge->target->index ];
            vIndex++;
        }
        else {
            newHalfEdges[2*k].target = newHalfEdges[2*m].target;
            newHalfEdges[2*k+1].target = &newVertices[ faces.size() + currentEdge->target->index ];

            // Assign Twins
            newHalfEdges[2*k].twin = &newHalfEdges[2*m+1];
            newHalfEdges[2*k+1].twin = &newHalfEdges[2*m];
            newHalfEdges[2*m].twin = &newHalfEdges[2*k+1];
            newHalfEdges[2*m+1].twin = &newHalfEdges[2*k];

            // Boundary edges are added last when importing a mesh, so their index will always be higher than their twins.
            if (!currentEdge->polygon) {
                newHalfEdges[2*k].next = &newHalfEdges[2*k+1];
                newHalfEdges[2*k+1].prev = &newHalfEdges[2*k];

                if (currentEdge > currentEdge->next) {
                    m = currentEdge->next->index;
                    newHalfEdges[2*k+1].next = &newHalfEdges[2*m];
                    newHalfEdges[2*m].prev = &newHalfEdges[2*k+1];
                }

                if (currentEdge > currentEdge->prev) {
                    m = currentEdge->prev->index;
                    newHalfEdges[2*k].prev = &newHalfEdges[2*m+1];
                    newHalfEdges[2*m+1].next = &newHalfEdges[2*k];
                }
            }
        }
    }

    // Note that Next, Prev and Poly are not yet assigned at this point.

}
