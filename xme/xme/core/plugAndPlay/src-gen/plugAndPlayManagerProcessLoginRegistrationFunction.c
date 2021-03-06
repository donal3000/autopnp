/*
 * Copyright (c) 2011-2014, fortiss GmbH.
 * Licensed under the Apache License, Version 2.0.
 *
 * Use, modification and distribution are subject to the terms specified
 * in the accompanying license file LICENSE.txt located at the root directory
 * of this software distribution. A copy is available at
 * http://chromosome.fortiss.org/.
 *
 * This file is part of CHROMOSOME.
 *
 * $Id: plugAndPlayManagerProcessLoginRegistrationFunction.c 7837 2014-03-14 12:33:13Z wiesmueller $
 */

/**
 * \file
 *         Source file for function pnpManagerProcessLoginRegistration in component pnpManager.
 *
 * \author
 *         This file has been generated by the CHROMOSOME Modeling Tool (XMT)
 *         (fortiss GmbH).
 */

/******************************************************************************/
/***   Includes                                                             ***/
/******************************************************************************/
#include "xme/core/plugAndPlay/include-gen/plugAndPlayManagerProcessLoginRegistrationFunction.h"

#include "xme/core/plugAndPlay/include-gen/plugAndPlayManagerProcessLoginRegistrationFunctionWrapper.h"
#include "xme/core/plugAndPlay/include-gen/plugAndPlayManagerComponent.h"
#include "xme/core/plugAndPlay/include-gen/plugAndPlayManagerComponentWrapper.h"
#include "xme/core/plugAndPlay/include-gen/pnpManagerManifest.h"

#include "xme/core/logUtils.h"

#include "xme/hal/include/mem.h"

// PROTECTED REGION ID(XME_CORE_PNP_PNPMANAGERPROCESSLOGINREGISTRATIONFUNCTION_C_INCLUDES) ENABLED START
#include "xme/core/plugAndPlay/include/plugAndPlayManager.h"
#include "xme/hal/include/mem.h"
#include "xme/wp/waypointConfigInfrastructure.h"
#include <inttypes.h>
// PROTECTED REGION END

/******************************************************************************/
/***   Definitions                                                          ***/
/******************************************************************************/

// PROTECTED REGION ID(XME_CORE_PNP_PNPMANAGERPROCESSLOGINREGISTRATIONFUNCTION_C_DEFINITIONS) ENABLED START

// PROTECTED REGION END

/******************************************************************************/
/***   Variables                                                            ***/
/******************************************************************************/
/**
 * \brief  Variable holding the value of the required output port 'outPnPLoginResponse'.
 *
 * \details If necessary initialize this in the init function.
 *          The value of this variable will be written to the port at the end of
 *          the step function.
 */
static xme_core_topic_login_pnpLoginResponse_t
portOutPnPLoginResponseData;

// PROTECTED REGION ID(XME_CORE_PNP_PNPMANAGERPROCESSLOGINREGISTRATIONFUNCTION_C_VARIABLES) ENABLED START

// PROTECTED REGION END

/******************************************************************************/
/***   Prototypes                                                           ***/
/******************************************************************************/

// PROTECTED REGION ID(XME_CORE_PNP_PNPMANAGERPROCESSLOGINREGISTRATIONFUNCTION_C_PROTOTYPES) ENABLED START

// PROTECTED REGION END

/******************************************************************************/
/***   Implementation                                                       ***/
/******************************************************************************/
xme_status_t
xme_core_pnp_pnpManagerProcessLoginRegistrationFunction_init
(
    xme_core_pnp_pnpManagerComponent_config_t* const componentConfig
)
{
    // PROTECTED REGION ID(XME_CORE_PNP_PNPMANAGERPROCESSLOGINREGISTRATIONFUNCTION_INITIALIZE_C) ENABLED START

    // Nothing to do

    XME_UNUSED_PARAMETER(componentConfig);

    return XME_STATUS_SUCCESS;

    // PROTECTED REGION END
}

void
xme_core_pnp_pnpManagerProcessLoginRegistrationFunction_step
(
    xme_core_pnp_pnpManagerComponent_config_t* const componentConfig
)
{
    xme_status_t status[1];
    
    xme_core_topic_login_pnpLoginRequest_t portInPnPLoginRequestData; // Required port.
    xme_core_topic_login_pnpLoginResponse_t* portOutPnPLoginResponseDataPtr = &portOutPnPLoginResponseData;
    
    (void)xme_hal_mem_set(&portInPnPLoginRequestData, 0u, sizeof(xme_core_topic_login_pnpLoginRequest_t));
    
    status[0] = xme_core_pnp_pnpManagerComponentWrapper_readPortInPnPLoginRequest(&portInPnPLoginRequestData);
    
    {
        // PROTECTED REGION ID(XME_CORE_PNP_PNPMANAGERPROCESSLOGINREGISTRATIONFUNCTION_STEP_C) ENABLED START

        xme_com_interface_address_t interfaceAddress;
        xme_com_interface_address_t* pnpManagerInterfaceAddress;
        char strIPAddress[XME_COM_INTERFACE_IPV4_STRING_BUFFER_SIZE];
        xme_core_channelId_t channelID;

        pnpManagerInterfaceAddress = (xme_com_interface_address_t*) xme_hal_mem_alloc(sizeof(xme_com_interface_address_t));

        XME_UNUSED_PARAMETER(componentConfig);
        XME_CHECK_MSG
        (
            XME_STATUS_SUCCESS == status[0],
            XME_CHECK_RVAL_VOID,
            XME_LOG_WARNING,
            "[PnPManager] Read of port inPnPLoginRequest failed.\n"
        );

        XME_CHECK_MSG
        (
            XME_STATUS_SUCCESS == xme_com_interface_ipv4ToGenericAddress
            (
                portInPnPLoginRequestData.ipAddress,
                portInPnPLoginRequestData.ipAddress >> 8,
                portInPnPLoginRequestData.ipAddress >> 16,
                portInPnPLoginRequestData.ipAddress >> 24,
                xme_hal_net_ntohs(portInPnPLoginRequestData.portAddress),
                &interfaceAddress
            ),
            XME_CHECK_RVAL_VOID,
            XME_LOG_ERROR,
            "[PnPManager] Cannot get the interface address from the pnp login request.\n"
        );

        XME_CHECK_MSG
        (
            XME_STATUS_SUCCESS == xme_com_interface_genericAddressToIPv4String
            (
                &interfaceAddress, strIPAddress, XME_COM_INTERFACE_IPV4_STRING_BUFFER_SIZE
            ),
            XME_CHECK_RVAL_VOID,
            XME_LOG_ERROR,
            "[PnPManager] Cannot transform ip address to string.\n"
        );

        XME_CHECK_MSG
        (
            XME_STATUS_SUCCESS == xme_wp_wci_addConfig(portInPnPLoginRequestData.ipAddress, portInPnPLoginRequestData.portAddress,
                                                           (xme_core_channelId_t) XME_CORE_TOPIC_PNPMANAGER_RUNTIME_GRAPH_MODEL, XME_CORE_TOPIC_PNPMANAGER_RUNTIME_GRAPH_MODEL),
            XME_CHECK_RVAL_VOID,
            XME_LOG_ERROR,
            "[PnPManager] Cannot generate waypoint configuration for sending runtime graphs.\n"
        );

        XME_LOG
        (
            XME_LOG_DEBUG,
            "[PnPManager] Received a PnP Login Request for node %d with IP address %s.\n",
            portInPnPLoginRequestData.nodeId,
            strIPAddress
        );

        XME_CHECK_MSG
        (
            XME_STATUS_SUCCESS == xme_core_pnp_pnpManager_registerNode(portInPnPLoginRequestData.nodeId),
            XME_CHECK_RVAL_VOID,
            XME_LOG_ERROR,
            "[PnPManager] The node registration cannot be registered in the plug and play manager.\n"
        );

        XME_CHECK_MSG
        (
            XME_STATUS_SUCCESS == xme_core_pnp_pnpManager_generateChannelIDForManifestReception(portInPnPLoginRequestData.nodeId, &channelID),
            XME_CHECK_RVAL_VOID,
            XME_LOG_ERROR,
            "[PnPManager] Cannot generate a new channel identifier.\n"
        );

        XME_CHECK_MSG
        (
            XME_STATUS_SUCCESS == xme_core_pnp_pnpManager_registerInterfaceAddress(portInPnPLoginRequestData.nodeId, interfaceAddress),
            XME_CHECK_RVAL_VOID,
            XME_LOG_ERROR,
            "[PnPManager] The interface address (%s) associated to the node %d was unsuccessful.\n",
            strIPAddress,
            portInPnPLoginRequestData.nodeId
        );

        XME_CHECK_MSG
        (
            XME_STATUS_SUCCESS == xme_core_node_getInterface(pnpManagerInterfaceAddress),
            XME_CHECK_RVAL_VOID,
            XME_LOG_ERROR,
            "Cannot get the interface from node component.\n"
        );

        portOutPnPLoginResponseDataPtr->nodeId = portInPnPLoginRequestData.nodeId;
        portOutPnPLoginResponseDataPtr->channelID = channelID;
        XME_CHECK_MSG
        (
            XME_STATUS_SUCCESS == xme_com_interface_genericAddressToIPv4
            (
                pnpManagerInterfaceAddress,
                &portOutPnPLoginResponseDataPtr->ipAddress,
                &portOutPnPLoginResponseDataPtr->portAddress
            ),
            XME_CHECK_RVAL_VOID,
            XME_LOG_ERROR,
            "Cannot set the interface in the pnpLoginResponse.\n"
        );

        XME_CHECK_MSG
        (
            XME_STATUS_SUCCESS == xme_com_interface_genericAddressToIPv4String
            (
                pnpManagerInterfaceAddress, strIPAddress, XME_COM_INTERFACE_IPV4_STRING_BUFFER_SIZE
            ),
            XME_CHECK_RVAL_VOID,
            XME_LOG_ERROR,
            "Cannot transform ip address to string.\n"
        );

        XME_LOG
        (
            XME_LOG_DEBUG,
            "[PnPManager] Sending a PnP Login Response for node %d and IP address: %s\n",
            portInPnPLoginRequestData.nodeId,
            strIPAddress
        );

        // PROTECTED REGION END
    }
    
    status[0] = xme_core_pnp_pnpManagerComponentWrapper_writePortOutPnPLoginResponse(portOutPnPLoginResponseDataPtr);
    
    {
        // PROTECTED REGION ID(XME_CORE_PNP_PNPMANAGERPROCESSLOGINREGISTRATIONFUNCTION_STEP_2_C) ENABLED START

        XME_CHECK_MSG
        (
            XME_STATUS_SUCCESS == status[0] ||
            XME_STATUS_INVALID_PARAMETER == status[0], // This parameter is when we are not producing data.
            XME_CHECK_RVAL_VOID,
            XME_LOG_WARNING,
            "The write port operation failed."
        );

        // PROTECTED REGION END
    }
}

void
xme_core_pnp_pnpManagerProcessLoginRegistrationFunction_fini
(
    xme_core_pnp_pnpManagerComponent_config_t* const componentConfig
)
{
    // PROTECTED REGION ID(XME_CORE_PNP_PNPMANAGERPROCESSLOGINREGISTRATIONFUNCTION_TERMINATE_C) ENABLED START

    // Nothing to do

    XME_UNUSED_PARAMETER(componentConfig);

    // PROTECTED REGION END
}

// PROTECTED REGION ID(XME_CORE_PNP_PNPMANAGERPROCESSLOGINREGISTRATIONFUNCTION_IMPLEMENTATION_C) ENABLED START

// PROTECTED REGION END
