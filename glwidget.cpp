#include "glwidget.h"
#include <GL/GLU.h>
#include <OpenGL/freeglut.h>

#include "common.h"

GLWidget::GLWidget(QWidget *parent)
	: QGLWidget(parent)
{
	spin = 0.f;
	size = 0;
	
	point_size = 1;

	/*last_pos.setX(-1);
	last_pos.setY(-1);*/
	draw_rect = false;

	scale = 1.;

	vertices.resize(size);
	colors.resize(size);

	vertex_array = NULL;
	color_array = NULL;

	vertex_array = new GLfloat *[100];
	color_array = new GLubyte *[100];
	
	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) {
			int index = i * 10 + j;
			vertex_array[index] = new GLfloat[2];
			vertex_array[index][0] = (i + 1) / 10.;
			vertex_array[index][1] = (j + 1) / 10.;

			color_array[index] = new GLubyte[3];
			color_array[index][0] = rand() % 256;
			color_array[index][1] = rand() % 256;
			color_array[index][2] = rand() % 256;
		}
	}

}

GLWidget::~GLWidget()
{
}

void GLWidget::initializeGL()
{
	QGLWidget::initializeGL();
	glewInit();

	// 此处开始对OpenGL进行所有设置
	//glShadeModel(GL_SMOOTH);						// 启用阴影平滑
	glShadeModel(GL_FLAT);

	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f);					// 黑色背景
	//glClearColor( 1.0f, 1.0f, 1.0f, 1.0f);					// 白色背景

	//glClearDepth(1.0f);							// 设置深度缓存
	//glEnable(GL_DEPTH_TEST);						// 启用深度测试
	//glDepthFunc(GL_LEQUAL);							// 所作深度测试的类型
	//glDisable( GL_LIGHTING);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// 告诉系统对透视进行修正

	glGenBuffers( 1, &vertex_vbo);
	glBindBuffer( GL_ARRAY_BUFFER, vertex_vbo);
	//glBufferData( GL_ARRAY_BUFFER, size * 3 * sizeof(GLfloat), vertex_array, GL_DYNAMIC_DRAW);
	glBufferData( GL_ARRAY_BUFFER, 100 * 2 * sizeof(GLfloat), vertex_array, GL_STATIC_DRAW);
	//glBindBuffer( GL_ARRAY_BUFFER, 0);

	glGenBuffers( 1, &color_vbo);
	glBindBuffer( GL_ARRAY_BUFFER, color_vbo);
	//glBufferData( GL_ARRAY_BUFFER, size * 3 * sizeof(GLubyte), color_array, GL_DYNAMIC_DRAW);
	glBufferData( GL_ARRAY_BUFFER, 100 * 3 * sizeof(GLubyte), color_array, GL_STATIC_DRAW);
	//glBindBuffer( GL_ARRAY_BUFFER, 0);

}

void GLWidget::paintGL()
{
	// call the function that does rendering here
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glScalef(scale, scale, scale);
	glPointSize( point_size);
    glBegin(GL_POINTS);
	for(int i = 0; i < size; i++) {
		glColor3f(colors[i].val[0], colors[i].val[1],colors[i].val[2]);
		glVertex2f(vertices[i].val[0], vertices[i].val[1]);
	}
    glEnd();

	if(draw_rect) {
		glBegin(GL_LINES);
		float sx = min(last_pos.x, cur_pos.x), bx = max(last_pos.x, cur_pos.x);
		float sy = min(last_pos.y, cur_pos.y), by = max(last_pos.y, cur_pos.y);
		glColor3f(1., 0., 0.);
		glVertex2f(sx, sy);
		glVertex2f(sx, by);

		glVertex2f(sx, by);
		glVertex2f(bx, by);

		glVertex2f(bx, by);
		glVertex2f(bx, sy);

		glVertex2f(bx, sy);
		glVertex2f(sx, sy);
		//glRectf(last_pos.x, last_pos.y , cur_pos.x, cur_pos.y);
		glEnd();
	}

	/*glPushMatrix();
	glRotatef(spin, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glRectf(0., 0., 0.5, 0.5);
	glPopMatrix();*/

	/*glLoadIdentity();
	// glScale
	//glBindBuffer( GL_ARRAY_BUFFER, vertex_vbo);
	//glBindBuffer( GL_ARRAY_BUFFER, color_vbo);

	//glVertexPointer( 2, GL_FLOAT, 0, 0);
	//glColorPointer( 3, GL_UNSIGNED_BYTE, 0, 0);

	glEnableClientState( GL_VERTEX_ARRAY);
	glEnableClientState( GL_COLOR_ARRAY);

	glVertexPointer( 2, GL_FLOAT, 0, vertex_array);
	glColorPointer( 3, GL_UNSIGNED_BYTE, 0, color_array);

    glColor3f(1,1,0);
	glPointSize( 5.);
    glBegin(GL_POINTS);
	glArrayElement(2);
	glArrayElement(7);
	glArrayElement(50);
    glEnd();
	//glDrawArrays( GL_POINTS, 0, 10);
	//glDrawElementArrayAPPLE(<#GLenum mode#>, <#GLint first#>, <#GLsizei count#>)

	glDisableClientState( GL_VERTEX_ARRAY);
	glDisableClientState( GL_COLOR_ARRAY);*/
	//glutSwapBuffers();
	//swapBuffers();
}

void GLWidget::resizeGL(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-width, width, -height, height, -1.0, 1.0);
	gluOrtho2D(0., 1., 0., 1.); // 设定裁切窗口（空间/平面哪一部分被显示）
	glViewport(0, 0, width, height); // 设定视口（屏幕哪一部分用于显示）
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/* On mouse press button events */
void GLWidget::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton) {
	}
	else if(event->button() == Qt::RightButton) {
	}
	else {
	}
	last_pos.x = 1. * event->x() * scale / width();
	last_pos.y = (height() - 1. * event->y() * scale) / height();

	int x = event->x(), y = event->y();

	//QString info = "mouse (local) point: (" + QString::number(x) + ", " + QString::number(y) + ").";

	//emit showInfo(info);

	updateGL();
}

/* On mouse move button events */
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	
	int x = event->x(), y = event->y();
	cur_pos.x = 1. * event->x() * scale / width();
	cur_pos.y = (height() - 1. * event->y() * scale) / height();
	draw_rect = true;

	emit giveRange(last_pos, cur_pos);

	/*QString info = "mouse (local) point: (" + QString::number(x) + ", " + QString::number(y) + ").\n";

	info.append("rect p1: (" + QString::number(last_pos.x) + ", " + QString::number(last_pos.y) + ").\n");
	info.append("rect p2: (" + QString::number(cur_pos.x) + ", " + QString::number(cur_pos.y) + ").\n");*/

	//emit showInfo(info);

	updateGL();
}

/* On mouse release button events */
void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{

	/*int x = event->x(), y = event->y();

	QString info = "mouse (local) point: (" + QString::number(x) + ", " + QString::number(y) + ").";

	emit showInfo(info);*/
	draw_rect = false;

	updateGL();	
}

void GLWidget::wheelEvent(QWheelEvent *event) {

	int num = event->delta();
	int x = event->x(), y = event->y();

	scale += num / 12000.;

	QString info = "mouse (local) point: (" + QString::number(x) + ", " + QString::number(y) + "): " + QString::number(scale);
	emit showInfo(info);
	updateGL();	
}

/* On keybord press events */
void GLWidget::keyPressEvent(QKeyEvent *event)
{

	updateGL();
}

/* On keyboard button events */
void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
	updateGL();
}


//void GLWidget::updatePoints(const std::vector<KD_Point<double> > * points_pt) {
void GLWidget::updatePoints(void * pt) {

	std::vector<KD_Point<double> > * points_pt = (std::vector<KD_Point<double> > *) pt;
	if(points_pt != NULL) {
		size = points_pt->size();
		vertices.resize(size);
		colors.resize(size);
		for(int i = 0; i < size; i++) {
			vertices[i].val[0] = (*points_pt)[i].x;
			vertices[i].val[1] = (*points_pt)[i].y;

			colors[i].val[0] = colors[i].val[1] = colors[i].val[2] = 255;
		}
	}

	QString str = "";
	for(int i = 0; i < size; i++) {
		str.append("(" + QString::number(vertices[i].val[0]) + ", " + QString::number(vertices[i].val[1]) + ")\n");
	}
	emit showInfo(str);

	updateGL();
}

void GLWidget::updateSelectedPoints(void * pt) {

	std::vector<KD_Point<double> > * selected_pt = (std::vector<KD_Point<double> > *) pt;
	if(selected_pt != NULL) {
		for(int i = 0; i < size; i++) {
			colors[i].val[0] = colors[i].val[1] = colors[i].val[2] = 255;
		}
		for(int i = 0; i < selected_pt->size(); i++) {
			int index = (*selected_pt)[i].index;
			colors[index].val[0] = 255;
			colors[index].val[1] = 0;
			colors[index].val[2] = 0;
		}
	}

	updateGL();
}

void GLWidget::updatePointSize(int sz) {
	point_size = sz;

	updateGL();
}
