/*
 *  Yarp Modules Manager
 *  Copyright: 2011 (C) Robotics, Brain and Cognitive Sciences - Italian Institute of Technology (IIT)
 *  Authors: Ali Paikan <ali.paikan@iit.it>
 * 
 *  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#ifndef _MODULE_PROPERTY_WINDOW_H_
#define _MODULE_PROPERTY_WINDOW_H_

#include <gtkmm.h>
#include "module.h"
#include "manager.h"

class MainWindow;

class ModulePropItemColumns : public Gtk::TreeModel::ColumnRecord
{
public:

    ModulePropItemColumns() { 
        add(m_col_name); 
        add(m_col_value);
        add(m_col_color_item);
        add(m_col_color_value);
        add(m_col_editable);
    }

    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
    Gtk::TreeModelColumn<Glib::ustring> m_col_value;
    Gtk::TreeModelColumn<Gdk::Color> m_col_color_item;
    Gtk::TreeModelColumn<Gdk::Color> m_col_color_value;
    Gtk::TreeModelColumn<bool> m_col_editable;
};


class ModulePropertyWindow: public Gtk::ScrolledWindow
{
public:
    ModulePropertyWindow(MainWindow* parent, Manager* manager);
    virtual ~ModulePropertyWindow();

    void onTabCloseRequest();
    void onRefresh();

    void update(Module* module);
    void release(void) { m_pModule = NULL; m_pIModule = NULL; } 
    Module* getModule(void) { return m_pModule; }
protected:
    void onCellData(Gtk::CellRenderer*, const Gtk::TreeModel::iterator& iter);
    void onCellEdited(const Glib::ustring& path_string, 
                    const Glib::ustring& new_text);
protected:
    ModulePropItemColumns m_Columns;  
    Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;
    Gtk::TreeView m_TreeView;

private:
    void updateModule(const char* item, const char* value);
    void updateParamteres(void);

    MainWindow* m_pParent;
    Module* m_pModule;
    ModuleInterface* m_pIModule;
    Manager* m_pManager;
};


#endif //_MODULE_PROPERTY_WINDOW_H_

