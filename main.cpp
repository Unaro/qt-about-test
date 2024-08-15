#include <QApplication>
#include <QTreeView>
#include <QStandardItemModel>
#include <QHBoxLayout>
#include <list>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    struct itemList {
        std::list<QStandardItem*> items;
        QStandardItem& foreginItem;

        itemList(QStandardItem& item, std::list<QStandardItem*> items) : items(items), foreginItem(item) {}
    };
    std::list<itemList*> items {};


    QWidget* widget = new QWidget;
    widget->setWindowTitle("Список модулей");
    widget->setMinimumHeight(150);
    widget->setMinimumWidth(250);

    QHBoxLayout *layout = new QHBoxLayout(widget);

    QStandardItemModel *model = new QStandardItemModel();
    QStandardItem *parentItem = model->invisibleRootItem();


    items.push_back(new itemList(*new QStandardItem("Оператор"), std::list<QStandardItem*> {new QStandardItem("Модуль 1"), new QStandardItem("Модуль 2")}));
    items.push_back(new itemList {*new QStandardItem("ЦОД"), std::list<QStandardItem*> {new QStandardItem("Модуль 1"), new QStandardItem("Модуль 2")}});

    for (itemList* item : items ) {
        parentItem->appendRow(&item->foreginItem);
        item->foreginItem.setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        for (QStandardItem* local_item : item->items)
        {
            item->foreginItem.appendRow(local_item);
            local_item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

        }
    }

    QTreeView *view = new QTreeView();
    view -> setHeaderHidden(true);
    view -> setModel(model);


    layout -> addWidget(view);


    widget->show();

    return a.exec();
}
