#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QPushButton>
#include <QMainWindow>
extern "C" {
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <glib-object.h>
#include <spice-client.h>
#include <spice-session.h>
#include <channel-main.h>
#include <channel-display.h>
#include <channel-inputs.h>
#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <spice-audio.h>
};

#include "spice-widget.h"


#ifndef SPICEQT_H
#define SPICEQT_H


class SpiceQt : public QWidget
{
    Q_OBJECT
public:
    SpiceQt(QWidget *parent = NULL);
    static SpiceQt *getSpice(QWidget *parent = NULL);
    //QSize spiceSize() { return QSize(dataWidth, dataHeight); }
    void connectToGuest(const QString &host, const QString &port);
    void disconnectFromGuest();
    void clearImage();
    SpiceAudio *spiceAudioGLib() { return audio; }
    void setSpiceAudioGLib(SpiceAudio *sa);
    SpiceDisplay *spiceDisplayGLib() { return display; }
    void setSpiceDisplayGLib(SpiceDisplay *sd);
    void updateImage(uchar *data, int x, int y, int width, int height);
    void settingsChanged(int width, int height, int bpp);
    void setKbdModifiers(int m);
    void spiceResize(int w, int h);
    void showCursor(bool visible)
    {
        if (visible)
            setCursor(Qt::ArrowCursor);
        else
            setCursor(Qt::BlankCursor);
    }
    quint32 getKeyboardLockModifiers();
    void setAgentConnected(bool connected) { agentConnected = connected; }
    bool getAgentConnected() { return agentConnected; }
    bool isRunning(){return true;}
protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    bool x11Event(XEvent *event);

//    bool eventFilter(QObject *obj, QEvent *event) override;

private Q_SLOTS:
    void printSize()
    {
        qDebug() << this->height() <<" ,  "<< this->width() << endl;
    }


Q_SIGNALS:
    void imageSize(int, int);
private:
    QTimer *timer;
    static QMap<int, int> * getKeymap();
    void prepareMouseData();
    static SpiceQt *instance;
    SpiceSession * SGsession;
    SpiceDisplay * display;
    SpiceAudio   * audio;
    uchar        * buf;
    QImage         img;
    int            dataWidth;
    int            dataHeight;
    double         rate;
    bool           scrollLock;
    bool           numLock;
    bool           capsLock;
    bool           agentConnected;
    static QMap<int, int>* keymap;
};

#endif SPICEQT_H
