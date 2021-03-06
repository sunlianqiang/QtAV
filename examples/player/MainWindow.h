#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

namespace QtAV {
class AudioOutput;
class AVPlayer;
class AVClock;
class VideoRenderer;
}

class QMenu;
class QTimeEdit;
class QVBoxLayout;
class QLabel;
class QPushButton;
class Button;
class Slider;
class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void enableAudio(bool yes = true);
    void setAudioOutput(QtAV::AudioOutput* ao);
    void setRenderer(QtAV::VideoRenderer* renderer);
    void play(const QString& name);

public slots:
    void openFile();
    void togglePlayPause();

signals:
    void ready();

private slots:
    void about();
    void help();
    void openUrl();
    void switchAspectRatio(QAction* action);
    void setRepeat(QAction* action);
    void changeVO(QAction* action);
    void playOnlineVideo(QAction* action);
    void processPendingActions();
    void initPlayer();
    void setupUi();
    void onSpinBoxChanged(double v);
    void onStartPlay();
    void onStopPlay();
    void onPaused(bool p);
    void onSpeedChange(qreal speed);
    void seekToMSec(int msec);
    void seek();
    void capture();
    void showHideVolumeBar();
    void setVolume();
    void tryHideControlBar();
    void tryShowControlBar();

protected:
    virtual void resizeEvent(QResizeEvent *);
    virtual void timerEvent(QTimerEvent *);
    void mouseMoveEvent(QMouseEvent *e);

private:
    bool mIsReady, mHasPendingPlay;
    bool mNullAO;
    int mShowControl; //0: can hide, 1: show and playing, 2: always show(not playing)
    int mTimerId;
    QVBoxLayout *mpPlayerLayout;

    QWidget *mpControl;
    QLabel *mpCurrent, *mpDuration;
    QLabel *mpTitle;
    QLabel *mpSpeed;
    Slider *mpTimeSlider, *mpVolumeSlider;
    Button *mpVolumeBtn;
    Button *mpPlayPauseBtn, *mpStopBtn, *mpForwardBtn, *mpBackwardBtn;
    Button *mpOpenBtn;
    Button *mpInfoBtn, *mpMenuBtn, *mpSetupBtn, *mpCaptureBtn;
    QMenu *mpMenu;
    QAction *mpVOAction, *mpARAction; //remove mpVOAction if vo.id() is supported
    QAction *mpRepeatAction;
    QList<QAction*> mVOActions;

    QtAV::AVClock *mpClock;
    QtAV::AVPlayer *mpPlayer;
    QtAV::VideoRenderer *mpRenderer, *mpTempRenderer;
    QString mFile;
    QPixmap mPlayPixmap;
    QPixmap mPausePixmap;
};

#endif // MAINWINDOW_H
