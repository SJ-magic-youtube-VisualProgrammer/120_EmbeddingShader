/************************************************************
************************************************************/
#include "ofApp.h"

/************************************************************
************************************************************/

/******************************
******************************/
void ofApp::setup(){
	/********************
	********************/
	ofSetWindowTitle("shaderSample");
	
	ofSetWindowShape( WINDOW_WIDTH, WINDOW_HEIGHT );
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	
	ofSetEscapeQuitsApp(false);
	
	/********************
	********************/
	img.load("img/img.png");
	
	/********************
	********************/
	// shader.load( "sj_shader/Gray.vert", "sj_shader/Gray.frag" );
	std::string str_fragment	= generateFrag();
	std::string str_vertex		= generateVert();
	
	shader.setupShaderFromSource(GL_VERTEX_SHADER, str_vertex);
	shader.setupShaderFromSource(GL_FRAGMENT_SHADER, str_fragment);
	shader.bindDefaults();
	shader.linkProgram();
}
/******************************
******************************/
std::string ofApp::generateVert() {
	std::stringstream src;
	
	src << "#version 120\n";
	src << "#extension GL_ARB_texture_rectangle : enable\n";
	src << "#extension GL_EXT_gpu_shader4 : enable\n";
	src << "\n";
	src << "void main() {\n";
	src << "\tgl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n";
	src << "\tgl_TexCoord[0] = gl_MultiTexCoord0;\n";
	src << "\tgl_FrontColor = gl_Color;\n";
	src << "}\n";
	
	return src.str();
}

/******************************
******************************/
std::string ofApp::generateFrag() {
	std::stringstream src;

	src << "/************************************************************\n";
	src << "ビルトイン関数(一部)\n";
	src << "\thttp://qiita.com/edo_m18/items/71f6064f3355be7e4f45\n";
	src << "************************************************************/\n";
	src << "#version 120\n";
	src << "#extension GL_ARB_texture_rectangle : enable\n";
	src << "#extension GL_EXT_gpu_shader4 : enable\n";
	src << "\n";
	src << "\n";
	src << "/************************************************************\n";
	src << "************************************************************/\n";
	src << "uniform sampler2DRect texture_0;\n";
	src << "\n";
	src << "/************************************************************\n";
	src << "************************************************************/\n";
	src << "\n";
	src << "/******************************\n";
	src << "******************************/\n";
	src << "void main(){\n";
	src << "\t/* */\n";
	src << "\tvec2 Coord = gl_TexCoord[0].xy;\n";
	src << "\t\n";
	src << "\t/* */\n";
	src << "\tvec4 color = texture2DRect( texture_0, Coord );\n";
	src << "\t\n";
	src << "\tfloat val = 0.299 * color.r + 0.587 * color.g + 0.114 * color.b;\n";
	src << "\tcolor = vec4(val, val, val, color.a);\n";
	src << "\t\n";
	src << "\tgl_FragColor = color * gl_Color;\n";
	src << "}\n";
	src << "\n";

	return src.str();
}

/******************************
******************************/
void ofApp::update(){

}

/******************************
******************************/
void ofApp::draw(){
	ofBackground(0, 0, 0, 255);
	// ofSetColor(255, 0, 0, 255);
	ofSetColor(255);
	
	if(b_UseShader)	shader.begin();
		img.draw(0, 0, ofGetWidth(), ofGetHeight());
	if(b_UseShader)	shader.end();
}

/******************************
******************************/
void ofApp::keyPressed(int key){
	switch(key){
		case 's':
			b_UseShader = !b_UseShader;
			break;
	}
}

/******************************
******************************/
void ofApp::keyReleased(int key){

}

/******************************
******************************/
void ofApp::mouseMoved(int x, int y ){

}

/******************************
******************************/
void ofApp::mouseDragged(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mousePressed(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseReleased(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseEntered(int x, int y){

}

/******************************
******************************/
void ofApp::mouseExited(int x, int y){

}

/******************************
******************************/
void ofApp::windowResized(int w, int h){

}

/******************************
******************************/
void ofApp::gotMessage(ofMessage msg){

}

/******************************
******************************/
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
