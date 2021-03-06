// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 *  Yarp Modules Manager
 *  Copyright: (C) 2012 Robotics, Brain and Cognitive Sciences - Italian Institute of Technology (IIT)
 *  Authors: Elena Ceseracciu, Ali Paikan <ali.paikan@iit.it>
 *
 *  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */


#ifndef __YARP_MANAGER_XMLAPPSAVER__
#define __YARP_MANAGER_XMLAPPSAVER__

#include <yarp/manager/ymm-types.h>
#include <yarp/manager/manifestloader.h>

namespace yarp {
namespace manager {


/**
 * Class XmlAppSaver
 */
class XmlAppSaver : public AppSaver
{

public:
    XmlAppSaver(const char* szFileName=NULL);
    virtual bool save(Application* application);
    virtual ~XmlAppSaver();

protected:

private:
    bool serialXml(Application* app, const char* szFile);
    std::string strFileName;
};

} // namespace yarp
} // namespace manager


#endif // __YARP_MANAGER_XMLAPPSAVER__
