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
 * $Id: receiverManifest.c 7769 2014-03-11 15:27:13Z geisinger $
 */

/**
 * \file
 *         Defines function for creation of component type manifest
 *         for 'receiver'.
 *
 * \author
 *         This file has been generated by the CHROMOSOME Modeling Tool (XMT)
 *         (fortiss GmbH).
 */

/******************************************************************************/
/***   Includes                                                             ***/
/******************************************************************************/
#include "queues/adv/receiver/include/receiverManifest.h"

#include "../include/receiverComponentWrapper.h"
#include "queues/adv/receiver/include/receiveFunction.h"
#include "queues/adv/receiver/include/receiveFunctionWrapper.h"
#include "queues/adv/receiver/include/receiverComponent.h"
#include "queues/topic/dictionary.h"
#include "xme/core/log.h"
#include "xme/hal/include/time.h"

/******************************************************************************/
/***   Implementation                                                       ***/
/******************************************************************************/
xme_status_t
queues_adv_receiver_manifest_createComponentTypeManifest
(
    xme_core_componentManifest_t* componentManifest
)
{
    XME_CHECK
    (
        NULL != componentManifest,
        XME_STATUS_INVALID_PARAMETER
    );

    (void)xme_hal_mem_set(componentManifest, 0U, sizeof(xme_core_componentManifest_t));

    componentManifest->componentType = (xme_core_componentType_t)4098;
    componentManifest->componentWrapperInit = queues_adv_receiver_receiverComponentWrapper_init;
    componentManifest->componentWrapperReceivePort = queues_adv_receiver_receiverComponentWrapper_receivePort;
    componentManifest->componentWrapperFini = queues_adv_receiver_receiverComponentWrapper_fini;
    componentManifest->componentInit = (xme_core_componentManifest_componentInit_t)queues_adv_receiver_receiverComponent_init;
    (void)xme_hal_safeString_strncpy(componentManifest->name, "receiver", sizeof(componentManifest->name));
    componentManifest->configStructSize = sizeof(queues_adv_receiver_receiverComponent_config_t);

    {
        uint32_t functionArrayLength = sizeof(componentManifest->functionManifests) / sizeof(componentManifest->functionManifests[0]);

        // Function 'receive'
        {
            if (0U >= functionArrayLength) // Check generated by tool (which does not know about the array size)
            {
                if (0U == functionArrayLength) // Only trigger warning once
                {
                    XME_LOG
                    (
                        XME_LOG_WARNING,
                        "%s:%d Component type 'receiver' defines more functions (%d) than can be stored in the manifest data structure (%d).\n",
                        __FILE__,
                        __LINE__,
                       1,
                       functionArrayLength
                    );
                }
            }
            else
            {
                xme_core_functionManifest_t* functionManifest;
                
                functionManifest = &componentManifest->functionManifests[0];
                functionManifest->functionId = (xme_core_component_functionId_t)1;
                functionManifest->wcet = xme_hal_time_timeIntervalFromMilliseconds(10ull);
                functionManifest->alphaCurve.alphaCurve = 0;
                functionManifest->completion = true;
                functionManifest->requiredPortIndicesLength = 0;
                functionManifest->optionalPortIndicesLength = 1;
                functionManifest->optionalPortIndices[0] = (queues_adv_receiver_receiverComponentWrapper_internalPortId_t)QUEUES_ADV_RECEIVER_RECEIVERCOMPONENTWRAPPER_PORT_IN;
                functionManifest->functionInit = (xme_core_exec_initCallback_t)queues_adv_receiver_receiveFunction_init;
                functionManifest->functionFini = (xme_core_exec_finiCallback_t)queues_adv_receiver_receiveFunction_fini;
                functionManifest->functionWrapperExecute = queues_adv_receiver_receiveFunctionWrapper_execute;
            }
        }
    }

    {
        uint32_t portArrayLength;
        portArrayLength = sizeof(componentManifest->portManifests) / sizeof(componentManifest->portManifests[0]);

        // Subscription 'in'
        {
            if (0 >= portArrayLength) // Check generated by tool (which does not know about the array size)
            {
                if (0 == portArrayLength) // Only trigger warning once
                {
                    XME_LOG
                    (
                        XME_LOG_WARNING,
                        "%s:%d Component type 'receiver' defines more ports (%d) than can be stored in the manifest data structure (%d).\n",
                        __FILE__,
                        __LINE__,
                        1,
                        portArrayLength
                    );
                }
            }
            else
            {
                xme_core_componentPortManifest_t* portManifest;
            
                portManifest = &componentManifest->portManifests[0];
                portManifest->portType = XME_CORE_COMPONENT_PORTTYPE_DCC_SUBSCRIPTION;
                portManifest->topic = QUEUES_TOPIC_DATA; 
                portManifest->lowerConnectionBound = 0u;
                portManifest->upperConnectionBound = XME_CORE_COMPONENT_CONNECTIONBOUND_UNBOUNDED;
                portManifest->queueSize = 2;
                portManifest->persistent = false;
        
                portManifest->attrSet = XME_CORE_ATTRIBUTE_EMPTY_ATTRIBUTE_SET;
            }
        }
    }
    return XME_STATUS_SUCCESS;
}