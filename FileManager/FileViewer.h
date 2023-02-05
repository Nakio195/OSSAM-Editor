#ifndef FileViewer_H
#define FileViewer_H

#include <QWidget>
#include <QMediaPlayer>
#include "FileManager/File.h"

namespace Ui {
class FileViewer;
}

class FileViewer : public QWidget
{
    Q_OBJECT

    public:
        explicit FileViewer(QWidget *parent = nullptr);
        ~FileViewer();

        void setFile(const File& File);

    public slots:
        void hideViewers();

        void updateTextureViewer();
        void updateFontViewer();
        void updateShaderViewer();
        void updateSoundViewer();

        void playSound();
        void soundDurationChanged(qint64 duration);
        void soundProgress(qint64 duration);
        void soundPlayerError(QMediaPlayer::Error error);
        void playState(QMediaPlayer::State state);
        void soundPlayerStatus(QMediaPlayer::MediaStatus status);

    private:
        Ui::FileViewer *ui;

        File mFile;

        int mLastLoadedFont;
        QMediaPlayer *mPlayer;
};

#endif // FileViewer_H
