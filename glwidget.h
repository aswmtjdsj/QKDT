#ifndef	GLWIDGET_H
#define GLWIDGET_H

#include <GL\glew.h>

#include <QGLWidget>
#include <QMouseEvent>

#include "kd_tree.h"

struct vertex{
	GLfloat val[3];
	vertex(){}
	vertex( GLfloat a, GLfloat b, GLfloat c = 0){
		val[0] = a;
		val[1] = b;
		val[2] = c;
	}
};
typedef vertex color;

class GLWidget : public QGLWidget
{
	Q_OBJECT

public:
	GLWidget(QWidget *parent = 0);
	virtual ~GLWidget() ;

signals:
	void showInfo(QString);
	void giveRange(KD_Point<double>, KD_Point<double>);

	public slots: 
		//void updatePoints(const std::vector<KD_Point<double> > *);
		void updatePoints(void *);
		void updateSelectedPoints(void *);
		void updatePointSize(int);

protected:
	virtual void initializeGL() override;
	virtual void paintGL() override;
	virtual void resizeGL(int width, int heigth) override;

	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void wheelEvent(QWheelEvent *event);

	virtual void keyPressEvent(QKeyEvent *event);
	virtual void keyReleaseEvent(QKeyEvent *event);

private:

	float spin;
	GLuint vertex_vbo, color_vbo;
	GLfloat ** vertex_array;
	GLubyte ** color_array;

	int size;
	int point_size;
	std::vector<vertex> vertices;
	std::vector<color> colors;

	KD_Point<double> last_pos, cur_pos;
	bool draw_rect;

	float scale;
};

#endif
