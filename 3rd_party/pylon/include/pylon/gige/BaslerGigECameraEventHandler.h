//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2019 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//-----------------------------------------------------------------------------
/**
\file
\brief Contains the camera event handler base class.
*/

#ifndef INCLUDED_BASLERGIGECAMERAEVENTHANDLER_H_3102315
#define INCLUDED_BASLERGIGECAMERAEVENTHANDLER_H_3102315

#include <pylon/stdinclude.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <GenApi/INode.h>

namespace Pylon
{
    class CBaslerGigEInstantCamera;

    /** \addtogroup Pylon_InstantCameraApiGigE
     * @{
     */

    /**
    \class  CBaslerGigECameraEventHandler
    \brief  The camera event handler base class.
    */
    class CBaslerGigECameraEventHandler
    {
    public:

        /**
        \brief This method is called when a camera event has been received.

        Only very short processing tasks should be performed by this method. Otherwise, the event notification will block the
        processing of images.

        \param[in]  camera The source of the call.
        \param[in]  userProvidedId  The ID passed when registering for the event. It can be used to distinguish between different events.
        \param[in]  pNode The node identified by node name when registering.

        \error
            C++ exceptions from this call will be caught and ignored. All event handlers are notified.
        \threading
            This method is called outside the lock of the camera object, outside the lock of the node map, and inside the lock of the camera event handler registry.
        */
        virtual void OnCameraEvent( CBaslerGigEInstantCamera& camera, intptr_t userProvidedId, GENAPI_NAMESPACE::INode* pNode)
        {
            PYLON_UNUSED(&camera);
            PYLON_UNUSED(userProvidedId);
            PYLON_UNUSED(pNode);
        }

        /**
        \brief This method is called when the camera event handler has been registered.

        \param[in]  camera The source of the call.
        \param[in]  nodeName  The name of the event data node updated on camera event, e.g. "ExposureEndEventTimestamp" for exposure end event.
        \param[in]  userProvidedId  This ID is passed as a parameter in CBaslerGigECameraEventHandler::OnCameraEvent and can be used to distinguish between different events.

        \error
            Exceptions from this call will propagate through.
        \threading
            This method is called inside the lock of the camera event handler registry.
        */
        virtual void OnCameraEventHandlerRegistered( CBaslerGigEInstantCamera& camera, const String_t& nodeName, intptr_t userProvidedId)
        {
            PYLON_UNUSED(&camera);
            PYLON_UNUSED(nodeName);
            PYLON_UNUSED(userProvidedId);
        }

        /**
        \brief This method is called when the camera event handler has been deregistered.

        The camera event handler is automatically deregistered when the Instant Camera object
        is destroyed.

        \param[in]  camera The source of the call.
        \param[in]  nodeName  The name of the event data node updated on camera event, e.g. "ExposureEndEventTimestamp" for exposure end event.
        \param[in]  userProvidedId  This ID is passed as a parameter in CBaslerGigECameraEventHandler::OnCameraEvent and can be used to distinguish between different events.

        \error
            C++ exceptions from this call will be caught and ignored.
        \threading
            This method is called inside the lock of the camera event handler registry.
        */
        virtual void OnCameraEventHandlerDeregistered( CBaslerGigEInstantCamera& camera, const String_t& nodeName, intptr_t userProvidedId)
        {
            PYLON_UNUSED(&camera);
            PYLON_UNUSED(nodeName);
            PYLON_UNUSED(userProvidedId);
        }

        /*!
        \brief Destroys the camera event handler.

        \error
            C++ exceptions from this call will be caught and ignored.
        */
        virtual void DestroyCameraEventHandler()
        {
            //If runtime errors occur here during delete, check the following:
            //Check that the cleanup procedure is correctly set when registering.
            //Ensure that the registered object has been allocated on the heap using new.
            //Ensure that the registered object has not already been deleted.
            delete this;
        }

        /// Create.
        CBaslerGigECameraEventHandler()
            : m_eventHandlerRegistrationCount(0)
        {
        }

        /// Copy.
        CBaslerGigECameraEventHandler(const CBaslerGigECameraEventHandler&)
            : m_eventHandlerRegistrationCount(0)
        {
        }

        /// Assign.
        CBaslerGigECameraEventHandler& operator=(const CBaslerGigECameraEventHandler&)
        {
            return *this;
        }

        /// Destruct.
        virtual ~CBaslerGigECameraEventHandler()
        {
            PYLON_ASSERT2( DebugGetEventHandlerRegistrationCount() == 0, "Error: The event handler must not be destroyed while it is registered.");
        }

        // Internal use only. Subject to change without notice.
        const long& DebugGetEventHandlerRegistrationCount()
        {
            return m_eventHandlerRegistrationCount;
        }

    private:
        long m_eventHandlerRegistrationCount; // Counts how many times the event handler is registered.
    };

    /**
     * @}
     */
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* INCLUDED_BASLERGIGECAMERAEVENTHANDLER_H_3102315 */
