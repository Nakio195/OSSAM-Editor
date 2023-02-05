#include "QSFMLView.h"
#include <QColorDialog>
#include <QDebug>

QSFMLView::QSFMLView(QWidget* Parent, const QPoint& Position, const QSize& Size, int FrameTime) :
    QWidget(Parent),
    mInitialized(false)
{
    // Mise en place de quelques options pour autoriser le rendu direct dans le widget
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    // Changement de la police de focus, pour autoriser notre widget à capter les évènements clavier
    setFocusPolicy(Qt::StrongFocus);

    // Définition de la position et de la taille du widget
    move(Position);
    resize(Size);

    // Préparation du timer
    mTimer.setInterval(FrameTime);

    sf::Vector2f size(static_cast<float>(QWidget::width()), static_cast<float>(QWidget::height()));
    sf::Vector2u sizeu(static_cast<unsigned int>(QWidget::width()), static_cast<unsigned int>(QWidget::height()));
    setSize(sizeu);
    mView.setSize(size);
    mView.setCenter(0, 0);
    setView(mView);

    mBackColor = QColor(127, 127, 127);
}

QSFMLView::~QSFMLView()
{

}

void QSFMLView::showEvent(QShowEvent*)
{
    if (!mInitialized)
    {
        // On crée la fenêtre SFML avec l'identificateur du widget
        sf::RenderWindow::create((sf::WindowHandle)(winId()));

        // On laisse la classe dérivée s'initialiser si besoin
        onInit();

        // On paramètre le timer de sorte qu'il génère un rafraîchissement à la fréquence souhaitée
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(repaint()));
        mTimer.start();

        mInitialized = true;
    }
}

float QSFMLView::getFrameTime()
{
    return mTimer.interval();
}

QPaintEngine* QSFMLView::paintEngine() const
{
    return nullptr;
}

void QSFMLView::resizeTo(sf::Vector2u size)
{
    resize(static_cast<int>(size.x), static_cast<int>(size.y));
}

void QSFMLView::mouseDoubleClickEvent(QMouseEvent *event)
{
    mBackColor = QColorDialog::getColor(mBackColor, this, "Couleur du fond #blancsurblanc");
}

void QSFMLView::resizeEvent(QResizeEvent*)
{
    sf::Vector2f size(static_cast<float>(QWidget::width()), static_cast<float>(QWidget::height()));
    sf::Vector2u sizeu(static_cast<unsigned int>(QWidget::width()), static_cast<unsigned int>(QWidget::height()));
    resize(QWidget::width(), QWidget::height());
    setSize(sizeu);
    mView.setSize(size);
    mView.setCenter(0, 0);
    setView(mView);
}


void QSFMLView::paintEvent(QPaintEvent*)
{
    // On laisse la classe dérivée faire sa tambouille
    setView(mView);
    onUpdate();


    if(QWidget::hasFocus())
    {
        QWidget::previousInFocusChain()->setFocus();
        qDebug() << "Giving back focus";
    }

    // On rafraîchit le widget
    display();
}
