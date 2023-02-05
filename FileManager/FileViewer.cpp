#include "FileViewer.h"
#include "ui_FileViewer.h"

#include <QFontDatabase>
#include <QMessageBox>
#include <QTime>

FileViewer::FileViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileViewer)
{
    ui->setupUi(this);

    mPlayer = new QMediaPlayer(this, QMediaPlayer::LowLatency);
    mPlayer->setAudioRole(QAudio::GameRole);
    mPlayer->setNotifyInterval(10);

    hideViewers();

    connect(ui->btn_Play, &QAbstractButton::clicked, this, &FileViewer::playSound);
    connect(mPlayer, QOverload<qint64>::of(&QMediaPlayer::durationChanged), this, &FileViewer::soundDurationChanged);
    connect(mPlayer, QOverload<qint64>::of(&QMediaPlayer::positionChanged), this, &FileViewer::soundProgress);
    connect(mPlayer, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), this, &FileViewer::soundPlayerError);
    connect(mPlayer, QOverload<QMediaPlayer::MediaStatus>::of(&QMediaPlayer::mediaStatusChanged), this, &FileViewer::soundPlayerStatus);
    connect(mPlayer, QOverload<QMediaPlayer::State>::of(&QMediaPlayer::stateChanged), this, &FileViewer::playState);
}

FileViewer::~FileViewer()
{
    delete ui;
    delete mPlayer;
}


void FileViewer::updateTextureViewer()
{
    QPixmap texture(mFile.getPath());

    QSize size = texture.size();

    if(texture.size().width() > 500)
        texture = texture.scaledToWidth(500);

    if(texture.size().height() > 500)
        texture = texture.scaledToHeight(500);

    ui->img_Texture->setPixmap(texture);
    ui->lbl_property->setText(QString("Largeur : ") + QString::number(size.width()) + " px\r\nHauteur : " + QString::number(size.height()) + " px");
    if(size != texture.size())
        ui->lbl_property->setText(ui->lbl_property->text() + "\r\n" + "(visualisation redimensionnée)");
}

void FileViewer::updateFontViewer()
{
    if(mLastLoadedFont != -1)
        QFontDatabase::removeApplicationFont(mLastLoadedFont);

    mLastLoadedFont = QFontDatabase::addApplicationFont(mFile.getPath());
    if(mLastLoadedFont == -1)
        return;

    QFontDatabase fonts;
    QFont font = fonts.font(QFontDatabase::applicationFontFamilies(mLastLoadedFont).first(), "Normal", 21);

    ui->fontEdit->setFont(font);

}

void FileViewer::updateShaderViewer()
{

}

void FileViewer::soundDurationChanged(qint64 duration)
{
    QTime time(0, 0);
    time = time.addMSecs(static_cast<int>(duration));
    ui->lbl_soundDuration->setText("Durée : " + time.toString("hh:mm:ss.zzz"));
    ui->progressBar->setRange(0, static_cast<int>(duration));
}

void FileViewer::soundProgress(qint64 position)
{
    ui->progressBar->setValue(static_cast<int>(position));
}

void FileViewer::soundPlayerError(QMediaPlayer::Error error)
{
    switch(error)
    {
        case QMediaPlayer::Error::ResourceError:
            QMessageBox::warning(this, "Preview audio", "Impossible de charger le son demandé...");
        break;
        case QMediaPlayer::Error::FormatError:
            QMessageBox::warning(this, "Preview audio", "Ce format audio n'est pas supporté !");
        break;

        default:
            QMessageBox::warning(this, "Preview audio", "Ca marche pas !");
            break;
    }
}

void FileViewer::soundPlayerStatus(QMediaPlayer::MediaStatus status)
{
    switch(status)
    {
        case QMediaPlayer::MediaStatus::NoMedia:
            ui->lbl_soundPlayerStatus->setText("Pas de fichier");
            break;
        case QMediaPlayer::MediaStatus::EndOfMedia:
            ui->lbl_soundPlayerStatus->setText("Terminé");
            break;
        case QMediaPlayer::MediaStatus::LoadedMedia:
            ui->lbl_soundPlayerStatus->setText("Son chargé");
            break;
        case QMediaPlayer::MediaStatus::InvalidMedia:
            ui->lbl_soundPlayerStatus->setText("Son invalide");
            break;
        case QMediaPlayer::MediaStatus::LoadingMedia:
            ui->lbl_soundPlayerStatus->setText("Chargement");
            break;
        case QMediaPlayer::MediaStatus::StalledMedia:
            ui->lbl_soundPlayerStatus->setText("Décrochage...");
            break;
        case QMediaPlayer::MediaStatus::BufferedMedia:
            ui->lbl_soundPlayerStatus->setText("Mise en cache terminée");
            break;
        case QMediaPlayer::MediaStatus::BufferingMedia:
            ui->lbl_soundPlayerStatus->setText("Mise en cache...");
            break;
        case QMediaPlayer::MediaStatus::UnknownMediaStatus:
            ui->lbl_soundPlayerStatus->setText("Statut inconnu...");
            break;
    }
}

void FileViewer::playSound()
{
    if(mPlayer->state() == QMediaPlayer::State::PausedState || mPlayer->state() == QMediaPlayer::State::StoppedState)
    {
        mPlayer->play();
    }
    else if(mPlayer->state() == QMediaPlayer::State::PlayingState)
    {
        mPlayer->pause();
    }
}

void FileViewer::playState(QMediaPlayer::State state)
{
    switch(state)
    {
        case QMediaPlayer::State::PausedState:
        case QMediaPlayer::State::StoppedState:
            ui->btn_Play->setText("Play");
            break;

        case QMediaPlayer::State::PlayingState:
            ui->btn_Play->setText("Pause");
            break;
    }
}

void FileViewer::updateSoundViewer()
{
    if(mPlayer->state() == QMediaPlayer::State::PlayingState)
    {
        mPlayer->pause();
        ui->btn_Play->setText(("Play"));
    }

    mPlayer->setMedia(QUrl::fromLocalFile(mFile.getPath()));
    mPlayer->setVolume(100);
}


void FileViewer::setFile(const File& file)
{
    mFile = file;

    hideViewers();

    switch(mFile.getType())
    {
        case File::Texture:
            updateTextureViewer();
            ui->view_Texture->show();
            break;
        case File::Font:
            updateFontViewer();
            ui->view_Font->show();
            break;
        case File::Shader:
            updateShaderViewer();
            ui->view_Shader->show();
            break;
        case File::Sound:
            updateSoundViewer();
            ui->view_Sound->show();
            break;

        default:
            hideViewers();
    }
}


void FileViewer::hideViewers()
{
    ui->view_Texture->hide();
    ui->view_Shader->hide();
    ui->view_Sound->hide();
    ui->view_Font->hide();
}
