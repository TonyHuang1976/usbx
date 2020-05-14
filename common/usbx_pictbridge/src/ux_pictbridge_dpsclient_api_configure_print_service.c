/**************************************************************************/
/*                                                                        */
/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
/*                                                                        */
/*       This software is licensed under the Microsoft Software License   */
/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
/*       and in the root directory of this software.                      */
/*                                                                        */
/**************************************************************************/


/**************************************************************************/
/**************************************************************************/
/**                                                                       */ 
/** USBX Component                                                        */ 
/**                                                                       */
/**   Pictbridge Application                                              */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/


/* Include necessary system files.  */

#define UX_SOURCE_CODE

#include "ux_api.h"
#include "ux_pictbridge.h"
#include "ux_device_class_pima.h"


/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    _ux_pictbridge_dpsclient_api_configure_print_service PORTABLE C     */ 
/*                                                           6.0          */
/*                                                                        */ 
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */ 
/*    This function creates the tag lines of the configure_print_service  */ 
/*    request and then output the request to the printer.                 */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    pictbridge                            Pictbridge instance           */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    Completion Status                                                   */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    _ux_utility_delay_ms                  Delay ms                      */ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    _ux_pictbridge_dpshost_object_get                                   */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */ 
/*                                                                        */ 
/*  05-19-2020     Chaoqiong Xiao           Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
UINT _ux_pictbridge_dpsclient_api_configure_print_service(UX_PICTBRIDGE *pictbridge) 
{
UINT                                status;
ULONG                               actual_flags;

    /* Wait for 100 ms to give a chance to the host to send a request before the client can post a Object Added event.  */
    _ux_utility_delay_ms(100);

    /* Prepare the object for configure print service. */
    status = _ux_pictbridge_dpsclient_input_object_prepare(pictbridge, UX_PICTBRIDGE_OR_CONFIGURE_PRINT_SERVICE, 0, 0);
    
    /* Check status.  */
    if (status != UX_SUCCESS)
        return(status);

    /* We should wait for the host to send a script with the response.  */
    status =  _ux_utility_event_flags_get(&pictbridge -> ux_pictbridge_event_flags_group, UX_PICTBRIDGE_EVENT_FLAG_CONFIGURE_PRINT_SERVICE, 
                                        TX_AND_CLEAR, &actual_flags, UX_PICTBRIDGE_EVENT_TIMEOUT);

    /* Check status.  */
    if (status != UX_SUCCESS)
        return(UX_EVENT_ERROR);

    /* Ensure the flag was set.  */
    if (actual_flags & UX_PICTBRIDGE_EVENT_FLAG_CONFIGURE_PRINT_SERVICE)
        
        /* Return completion status.  */
        return(UX_SUCCESS);    

    else
            
        /* Return completion status.  */
        return(UX_ERROR);    
}
