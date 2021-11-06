#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	float R = 200;
	float r = 80;
	int v_span = 90;
	int u_span = 15;

	ofMesh face, line;
	line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	for (int v = 0; v <=  360; v += v_span) {

		bool color_flag = true;
		bool flag = true;
		
		int u_start = v + ofGetFrameNum();
		int next_u = u_start + v_span;
		for (int u = u_start; u < u_start + 360; u += u_span) {

			if (flag) {

				vector<glm::vec3> vertices;
				vertices.push_back(this->make_point(R, r, u, v));
				vertices.push_back(this->make_point(R, r, u + u_span, v));
				vertices.push_back(this->make_point(R, r, next_u + u_span, v + v_span));
				vertices.push_back(this->make_point(R, r, next_u, v + v_span));

				face.addVertices(vertices);
				line.addVertices(vertices);

				ofColor face_color = color_flag ? ofColor(0) : ofColor(255);
				ofColor line_color = color_flag ? ofColor(255) : ofColor(0);
				color_flag = !color_flag;

				for (int i = 0; i < 4; i++) {

					face.addColor(face_color);
					line.addColor(line_color);
				}

				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 3);
				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 3); face.addIndex(face.getNumVertices() - 4);

				line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 4);
				line.addIndex(line.getNumVertices() - 2); line.addIndex(line.getNumVertices() - 3);
			}

			next_u += u_span;
			flag = !flag;
		}
	}

	face.drawFaces();
	line.drawWireframe();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
