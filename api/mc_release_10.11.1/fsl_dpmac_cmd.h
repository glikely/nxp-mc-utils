/* Copyright 2013-2016 Freescale Semiconductor Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * * Neither the name of the above-listed copyright holders nor the
 * names of any contributors may be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _FSL_DPMAC_CMD_H
#define _FSL_DPMAC_CMD_H

/* DPMAC Version */
#define DPMAC_VER_MAJOR			    4
#define DPMAC_VER_MINOR			    3
#define DPMAC_CMD_BASE_VERSION		1
#define DPMAC_CMD_2ND_VERSION       2
#define DPMAC_CMD_ID_OFFSET		    4

#define DPMAC_CMD(id)	(((id) << DPMAC_CMD_ID_OFFSET) | DPMAC_CMD_BASE_VERSION)
#define DPMAC_CMD_V2(id) (((id) << DPMAC_CMD_ID_OFFSET) | DPMAC_CMD_2ND_VERSION)

/* Command IDs */
#define DPMAC_CMDID_CLOSE		DPMAC_CMD(0x800)
#define DPMAC_CMDID_OPEN		DPMAC_CMD(0x80c)
#define DPMAC_CMDID_CREATE		DPMAC_CMD(0x90c)
#define DPMAC_CMDID_DESTROY		DPMAC_CMD(0x98c)
#define DPMAC_CMDID_GET_API_VERSION	DPMAC_CMD(0xa0c)

#define DPMAC_CMDID_GET_ATTR		DPMAC_CMD(0x004)
#define DPMAC_CMDID_RESET		DPMAC_CMD(0x005)

#define DPMAC_CMDID_SET_IRQ_ENABLE	DPMAC_CMD(0x012)
#define DPMAC_CMDID_GET_IRQ_ENABLE	DPMAC_CMD(0x013)
#define DPMAC_CMDID_SET_IRQ_MASK	DPMAC_CMD(0x014)
#define DPMAC_CMDID_GET_IRQ_MASK	DPMAC_CMD(0x015)
#define DPMAC_CMDID_GET_IRQ_STATUS	DPMAC_CMD(0x016)
#define DPMAC_CMDID_CLEAR_IRQ_STATUS	DPMAC_CMD(0x017)

#define DPMAC_CMDID_GET_LINK_CFG	DPMAC_CMD_V2(0x0c2)
#define DPMAC_CMDID_SET_LINK_STATE	DPMAC_CMD_V2(0x0c3)
#define DPMAC_CMDID_GET_COUNTER		DPMAC_CMD(0x0c4)

/* Macros for accessing command fields smaller than 1byte */
#define DPMAC_MASK(field)        \
	GENMASK(DPMAC_##field##_SHIFT + DPMAC_##field##_SIZE - 1, \
		DPMAC_##field##_SHIFT)
#define dpmac_set_field(var, field, val) \
	((var) |= (((val) << DPMAC_##field##_SHIFT) & DPMAC_MASK(field)))
#define dpmac_get_field(var, field)      \
	(((var) & DPMAC_MASK(field)) >> DPMAC_##field##_SHIFT)

#pragma pack(push, 1)
struct dpmac_cmd_open {
	uint32_t dpmac_id;
};

struct dpmac_cmd_create {
	uint32_t mac_id;
};

struct dpmac_cmd_destroy {
	uint32_t dpmac_id;
};

struct dpmac_cmd_set_irq_enable {
	uint8_t enable;
	uint8_t pad[3];
	uint8_t irq_index;
};

struct dpmac_cmd_get_irq_enable {
	uint32_t pad;
	uint8_t irq_index;
};

struct dpmac_rsp_get_irq_enable {
	uint8_t enabled;
};

struct dpmac_cmd_set_irq_mask {
	uint32_t mask;
	uint8_t irq_index;
};

struct dpmac_cmd_get_irq_mask {
	uint32_t pad;
	uint8_t irq_index;
};

struct dpmac_rsp_get_irq_mask {
	uint32_t mask;
};

struct dpmac_cmd_get_irq_status {
	uint32_t status;
	uint8_t irq_index;
};

struct dpmac_rsp_get_irq_status {
	uint32_t status;
};

struct dpmac_cmd_clear_irq_status {
	uint32_t status;
	uint8_t irq_index;
};

struct dpmac_rsp_get_attributes {
	uint8_t eth_if;
	uint8_t link_type;
	uint16_t id;
	uint32_t max_rate;
};

struct dpmac_rsp_get_link_cfg {
	uint64_t options;
	uint32_t rate;
    uint64_t advertising;
};

#define DPMAC_STATE_SIZE	1
#define DPMAC_STATE_SHIFT	0
#define DPMAC_STATE_VALID_SIZE 		1
#define DPMAC_STATE_VALID_SHIFT		1


struct dpmac_cmd_set_link_state {
	uint64_t  options;
	uint32_t  rate;
	uint32_t  pad;
	/* only least significant bit is valid */
	uint8_t  up;
    uint8_t  pad0[7];
    uint64_t supported;
    uint64_t advertising;

};

struct dpmac_cmd_get_counter {
	uint8_t type;
};

struct dpmac_rsp_get_counter {
	uint64_t pad;
	uint64_t counter;
};

struct dpmac_rsp_get_api_version {
	uint16_t major;
	uint16_t minor;
};
#pragma pack(pop)
#endif /* _FSL_DPMAC_CMD_H */
