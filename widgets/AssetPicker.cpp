#include "AssetPicker.h"
#include "ui_AssetPicker.h"

AssetPicker::AssetPicker(AssetModel *assets, QWidget *parent, Asset::Type type) : QDialog(parent), ui(new Ui::Dialog), mAssets(assets)
{
    ui->setupUi(this);

    ui->fileViewer->hide();
    ui->ln_search->setFocus();

    mSearched = false;
    mSearch.setFilterCaseSensitivity(Qt::CaseInsensitive);
    mSearch.setFilterKeyColumn(AssetModel::Name);

    if(type != Asset::Invalid)
    {
        mAssets->setType(type);
        mFiltered = true;
        mFilter.setSourceModel(mAssets);
        mFilter.setFilterKeyColumn(AssetModel::Type);
        mFilter.setFilterFixedString(Asset::TypeToText(type));

        mSearch.setSourceModel(&mFilter);
        ui->list->setModel(&mFilter);
    }

    else
    {
        mAssets->setType(Asset::Invalid);
        mFiltered = false;
        mSearch.setSourceModel(mAssets);
        ui->list->setModel(mAssets);
    }

    ui->list->setModelColumn(AssetModel::Name);
    ui->list->selectAll();

    connect(ui->list->selectionModel(), QOverload<const QModelIndex&, const QModelIndex&>::of(&QItemSelectionModel::currentRowChanged), this, &AssetPicker::selectionChanged);
    connect(ui->ln_search, &QLineEdit::textEdited, this, &AssetPicker::search);
    connect(ui->checkBox, &QCheckBox::toggled, ui->fileViewer, &QWidget::setVisible);
    connect(ui->list, &QListView::doubleClicked, this, &QDialog::accept);
}

AssetPicker::AssetPicker(AssetModel *assets, QWidget *parent, File::Type type) : QDialog(parent), ui(new Ui::Dialog), mAssets(assets)
{
    ui->setupUi(this);

    ui->fileViewer->hide();
    ui->ln_search->setFocus();

    mSearched = false;
    mSearch.setFilterCaseSensitivity(Qt::CaseInsensitive);
    mSearch.setFilterKeyColumn(AssetModel::Name);

    if(type != File::Invalid)
    {
        mAssets->setType(Asset::File);
        mFiltered = true;
        mFilter.setSourceModel(mAssets);
        mFilter.setFilterKeyColumn(AssetModel::Type);
        mFilter.setFilterFixedString(File::TypeToText(type));

        mSearch.setSourceModel(&mFilter);
        ui->list->setModel(&mFilter);
    }

    else
    {
        mAssets->setType(Asset::Invalid);
        mFiltered = false;
        mSearch.setSourceModel(mAssets);
        ui->list->setModel(mAssets);
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
    ui->fileViewer->setFile(*dynamic_cast<File*>(selectedAsset()));
}

void AssetPicker::search(QString string)
{
    if(!mFiltered)
    {
        if(string == QString(""))
        {
            ui->list->setModel(mAssets);
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

Asset* AssetPicker::selectedAsset()
{
    QModelIndex row = ui->list->selectionModel()->currentIndex();

    if(mFiltered && !mSearched)
        return mAssets->getByUID(Asset::Invalid, mAssets->getUID(mFilter.mapToSource(row)));

    else if(mFiltered && mSearched)
        return mAssets->getByUID(Asset::Invalid, mAssets->getUID(mFilter.mapToSource(mSearch.mapToSource(row))));

    else if(!mFiltered && mSearched)
        return mAssets->getByUID(Asset::Invalid, mAssets->getUID(mSearch.mapToSource(row)));

    else
        return mAssets->getByUID(Asset::Invalid, mAssets->getUID(row));
}

Asset* AssetPicker::pick(AssetModel* assets, QWidget *parent, Asset::Type type)
{
    AssetPicker picker(assets, parent, type);

    if(picker.exec() == QDialog::Accepted)
        return picker.selectedAsset();
    else
        return nullptr;
}

Asset* AssetPicker::pick(AssetModel* assets, QWidget *parent, File::Type type)
{
    AssetPicker picker(assets, parent, type);

    if(picker.exec() == QDialog::Accepted)
        return picker.selectedAsset();
    else
        return nullptr;
}
