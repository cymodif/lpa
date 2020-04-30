/***************************************************************************//**
* \file OlmInterface.c
* \version 1.0
*
* \brief
* Offload ManagerInterface
*
********************************************************************************
* \copyright
* Copyright 2020, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "cy_OlmInterface.h"
#include "cy_lpa_compat.h"
#include "cy_lpa_wifi_ol.h"
#include "cy_lpa_wifi_ol_common.h"
#include "cy_lpa_wifi_pf_ol.h"
#include "cy_lpa_wifi_olm.h"
#include "cy_lpa_wifi_arp_ol.h"
#include "cy_result_mw.h"

olm_t _olm;
whd_interface_t iface = NULL;

CYPRESS_WEAK const struct ol_desc *cycfg_get_default_ol_list()
{
    return NULL;
}

CYPRESS_WEAK const struct ol_desc *get_default_ol_list()
{
    return cycfg_get_default_ol_list();
}


void *cy_get_olm_instance()
{
    return &_olm;
}

cy_rslt_t cy_olm_create(void *ifp, ol_desc_t *oflds_list)
{
    ol_desc_t *olm_desc;
    cy_rslt_t result = CY_RSLT_SUCCESS;

    // Get Offload configuration from device configurator
    olm_desc = (ol_desc_t *)get_default_ol_list();
    if (olm_desc == NULL)
    {
        printf("Offloads not configured \n");
		olm_desc = oflds_list;
    }

    /* Offload Manager init */
    _olm.ol_info.whd = ifp;
    iface = ifp;
    olm_init(&_olm, olm_desc);

    return result;
}

cy_rslt_t cy_olm_init_ols(olm_t *olm, void *whd, void *ip)
{
    return olm_init_ols(olm, whd, ip);
}

void cy_olm_deinit_ols(olm_t *olm)
{
    olm_deinit_ols(olm);
}

void cy_olm_pm_notification_callback(olm_t *olm, ol_pm_st_t st)
{
    olm_dispatch_pm_notification(olm, st);
}

whd_interface_t cy_olm_get_whd_interface ( void )
{
	return iface;
}