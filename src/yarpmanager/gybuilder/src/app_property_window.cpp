/*
 *  Yarp Modules Manager
 *  Copyright: 2011 (C) Robotics, Brain and Cognitive Sciences - Italian Institute of Technology (IIT)
 *  Authors: Ali Paikan <ali.paikan@iit.it>
 * 
 *  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#if defined(WIN32)
    #pragma warning (disable : 4250)
    #pragma warning (disable : 4520)
#endif

#include "app_property_window.h"
#include "icon_res.h"
#include "ymm-dir.h"

#include "main_window.h"

ApplicationPropertyWindow::ApplicationPropertyWindow(MainWindow* parent, 
                               Manager* manager) : m_pApplication(NULL)
{   
    m_pParent = parent;
    m_pManager = manager;

    /* Create a new scrolled window, with scrollbars only if needed */
    set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    add(m_TreeView);

    /* create tree store */
    m_refTreeModel = Gtk::TreeStore::create(m_Columns);
    m_TreeView.set_model(m_refTreeModel);

    //Add the Model’s column to the View’s columns: 
    Gtk::CellRendererText* itemRenderer = Gtk::manage(new Gtk::CellRendererText());
    itemRenderer->property_editable() = false;
    Gtk::TreeViewColumn* itemCol = Gtk::manage(new Gtk::TreeViewColumn("Property", *itemRenderer));
    itemCol->add_attribute(*itemRenderer, "text", m_Columns.m_col_name);
    itemCol->set_resizable(true);
    m_TreeView.append_column(*itemCol);



    Gtk::CellRendererText* valueRenderer = Gtk::manage(new Gtk::CellRendererText());
    valueRenderer->property_editable() = false;
    Gtk::TreeViewColumn* valueCol = Gtk::manage(new Gtk::TreeViewColumn("Value", *valueRenderer));
    valueCol->add_attribute(*valueRenderer, "foreground-gdk", m_Columns.m_col_color_value);
    valueCol->add_attribute(*valueRenderer, "text", m_Columns.m_col_value);
    valueCol->set_resizable(true);
    valueRenderer->property_editable() = true;
    //valueCol->set_cell_data_func(*valueRenderer, sigc::mem_fun(*this,
    //    &ApplicationPropertyWindow::onCellData) );
    valueRenderer->signal_edited().connect( sigc::mem_fun(*this,
              &ApplicationPropertyWindow::onCellEdited) );
    m_TreeView.append_column(*valueCol);
    valueCol->add_attribute(*valueRenderer, "editable", m_Columns.m_col_editable);   

    //m_TreeView.append_column_editable("Value", m_Columns.m_col_value);
    //m_TreeView.get_column(1)->set_resizable(true);
       //Tell the view column how to render the model values:
    m_TreeView.set_grid_lines(Gtk::TREE_VIEW_GRID_LINES_BOTH);
    m_TreeView.set_rules_hint(true);

    show_all_children();
}


ApplicationPropertyWindow::~ApplicationPropertyWindow()
{
}

void ApplicationPropertyWindow::onRefresh()
{
    update(m_pApplication);
    m_pParent->reportErrors();
}

void ApplicationPropertyWindow::onTabCloseRequest() 
{ 
    m_pParent->onTabCloseRequest(this); 
}

void ApplicationPropertyWindow::update(Application* application)
{
    m_pApplication = application;
    //Application* m_pApplication = ApplicationPropertyWindow::m_pApplication;
    m_refTreeModel->clear();

    Gtk::TreeModel::Row row;
    Gtk::TreeModel::Row childrow;
    Gtk::TreeModel::Row cchildrow;

    row = *(m_refTreeModel->append());
    row[m_Columns.m_col_name] = "Name";
    row[m_Columns.m_col_value] = m_pApplication->getName();
    row[m_Columns.m_col_editable] = true;

    row = *(m_refTreeModel->append());
    row[m_Columns.m_col_name] = "Description";
    row[m_Columns.m_col_value] = m_pApplication->getDescription();
    row[m_Columns.m_col_editable] = true;

    row = *(m_refTreeModel->append());
    row[m_Columns.m_col_name] = "Version";
    row[m_Columns.m_col_value] = m_pApplication->getVersion();
    row[m_Columns.m_col_editable] = true;

    
    row = *(m_refTreeModel->append());
    row[m_Columns.m_col_name] = "Prefix";
    row[m_Columns.m_col_value] = m_pApplication->getPrefix();
    row[m_Columns.m_col_color_value] = Gdk::Color("#888888");
    row[m_Columns.m_col_editable] = false;

    row = *(m_refTreeModel->append());
    row[m_Columns.m_col_name] = "Authors";
    row[m_Columns.m_col_value] = "";
    row[m_Columns.m_col_editable] = false;
    for(int i=0; i<m_pApplication->authorCount(); i++)
    {
        childrow = *(m_refTreeModel->append(row.children()));
        childrow[m_Columns.m_col_name] = m_pApplication->getAuthorAt(i).getName();
        childrow[m_Columns.m_col_value] = m_pApplication->getAuthorAt(i).getEmail();
        childrow[m_Columns.m_col_editable] = true;
    }

    m_TreeView.expand_all();

}

void ApplicationPropertyWindow::updateApplication(const char* item, const char* value)
{
    /*
    // updating applications
    if(strcmp(item, "Node") == 0)
    {
        m_pApplication->setHost(value);
        if(m_pIApplication) m_pIApplication->setHost(value);
    }
    else if(strcmp(item,"Stdio") == 0)
    {
        m_pApplication->setStdio(value);
        if(m_pIApplication) m_pIApplication->setStdio(value);

    }
    else if(strcmp(item, "Workdir") == 0)
    {
        m_pApplication->setWorkDir(value);
        if(m_pIApplication) m_pIApplication->setWorkDir(value);

    }
    else if(strcmp(item, "Prefix") == 0)
    {    
        if(m_pIApplication)  
            m_pIApplication->setPrefix(value);

        Application* application = m_pManager->getKnowledgeBase()->getApplication(); 
        if(application)
        {
           string str_prefix = string(application->getPrefix()) + string(value); 
           m_pApplication->setPrefix(str_prefix.c_str());
        }
        else
            m_pApplication->setPrefix(value);

    }
    else if(strcmp(item, "Parameters") == 0)
    {
        m_pApplication->setParam(value);
        if(m_pIApplication) m_pIApplication->setParam(value);
    }
    */
}

void ApplicationPropertyWindow::onCellEdited(const Glib::ustring& path_string, 
                    const Glib::ustring& new_text)
{
    Gtk::TreePath path(path_string);

    //Get the row from the path:
    Gtk::TreeModel::iterator iter = m_refTreeModel->get_iter(path);
    if(iter)
    {
        Gtk::TreeModel::Row row = *iter;
        //Put the new value in the model:
        Glib::ustring strName = Glib::ustring(row[m_Columns.m_col_name]);
    
        row[m_Columns.m_col_value] = new_text;

        if(strName == "Name")
        {
            m_pApplication->setName(new_text.c_str());
        }

        if(strName == "Description")
        {
            m_pApplication->setDescription(new_text.c_str());
        }
     
        if(strName == "Version")
        {
            m_pApplication->setVersion(new_text.c_str());
        }

        /*
        if(strName == "Prefix")
        {
            m_pApplication->setName(new_text.c_str());
        }
        */
   }
}


