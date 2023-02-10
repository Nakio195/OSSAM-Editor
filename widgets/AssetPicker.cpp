#include "AssetPicker.h"
#include "ui_AssetPicker.h"

AssetPicker::AssetPicker(Context *context, QWidget *parent, Asset::Type type) : QDialog(parent), ui(new Ui::Dialog), mContext(context), mType(type)
{
    ui->setupUi(this);

    ui->fileViewer->hide();
    ui->ln_search->setFocus();

    mSearched = false;
    mSearch.setFilterCaseSensitivity(Qt::CaseInsensitive);
    mSearch.setFilterKeyColumn(AssetModel::Name);

    if(type != Asset::Invalid)
    {
        mFiltered = true;

        switch(type)
        {
            case Asset::File:
            case Asset::Texture:
            case Asset::Sound:
            case Asset::Shader:
            case Asset::Font:
                mSourceModel = mContext->files();
                break;

            case Asset::Animation:
                mSourceModel = mContext->animations();
                break;

            case Asset::Particle:
                mSourceModel = mContext->particles();
                break;
            default:
                assert(0);
        }

        mFilter.setSourceModel(mSourceModel);
        mFilter.setFilterKeyColumn(AssetModel::Type);
        mFilter.setFilterFixedString(Asset::TypeToText(type));

        mSearch.setSourceModel(&mFilter);
        ui->list->setModel(&mFilter);
    }

    else
    {
        mFiltered = false;
        mSourceModel = mContext->assets();
        mSearch.setSourceModel(mContext->assets());
        ui->list->setModel(mContext->assets());
    }

    ui->list->setModelColumn(AssetModel::Name);
    ui->list->selectAll();

    connect(ui->list->selectionModel(), QOverload<const QModelIndex&, const QModelIndex&>::of(&QItemSelectionModel::currentRowChanged), this, &AssetPicker::selectionChanged);
    connect(ui->ln_search, &QLineEdit::textEdited, this, &AssetPicker::search);
    connect(ui->checkBox, &QCheckBox::toggled, ui->fileViewer, &QWidget::setVisible);
    connect(ui->list, &QListView::doubleClicked, this, &QDialog::accept);
}

AssetPicker::~AssetPicker()
{
    delete ui;
}

void AssetPicker::selectionChanged(const QModelIndex&, const QModelIndex& )
{
    ui->fileViewer->setFile(mContext->files()->getByUID(selectedAsset()));
}

void AssetPicker::search(QString string)
{
    if(!mFiltered)
    {
        if(string == QString(""))
        {
            ui->list->setModel(mSourceModel);
            mSearched = false;
        }

        else
        {
            mSearch.setFilterFixedString(string);
            ui->list->setModel(&mSearch);
            mSearched = true;
        }
    }

    else
    {
        if(string == QString(""))
        {
            ui->list->setModel(&mFilter);
            mSearched = false;
        }

        else
        {
            mSearch.setFilterFixedString(string);
            ui->list->setModel(&mSearch);
            mSearched = true;
        }
    }
}

Asset::UID AssetPicker::selectedAsset()
{
    QModelIndex row = ui->list->selectionModel()->currentIndex();

    if(!row.isValid())
        return 0;

    if(mFiltered && !mSearched)
        row = mFilter.mapToSource(row);

    else if(mFiltered && mSearched)
        row = mFilter.mapToSource(mSearch.mapToSource(row));

    else if(!mFiltered && mSearched)
       row = mSearch.mapToSource(row);

    switch(mType)
    {
        case Asset::File:
        case Asset::Texture:
        case Asset::Sound:
        case Asset::Shader:
        case Asset::Font:
            return mContext->files()->getUID(row);
            break;

        case Asset::Animation:
            return mContext->animations()->getUID(row);
            break;

        case Asset::Particle:
            return mContext->particles()->getUID(row);
            break;
        default:
            assert(0);
    }

    return 0;
}

Asset::UID AssetPicker::pick(Context* context, QWidget *parent, Asset::Type type)
{
    AssetPicker picker(context, parent, type);

    if(picker.exec() == QDialog::Accepted)
        return picker.selectedAsset();
    else
        return 0;
}

