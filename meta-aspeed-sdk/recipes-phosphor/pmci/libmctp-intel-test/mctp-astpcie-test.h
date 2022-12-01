/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/*
 * Copyright 2021-2022 Aspeed Technology Inc.
 */
#ifndef _MCTP_ASTPCIE_TEST_H_
#define _MCTP_ASTPCIE_TEST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <libmctp.h>
#include <libmctp-log.h>
#include <libmctp-astpcie.h>
#include <libmctp-cmds.h>
#include <libmctp-msgtypes.h>

#define MCTP_MESSAGE_TYPE_ASPEED_ECHO_TEST 0x7c
#define MCTP_ASPEED_CTRL_CMD_ECHO 0x00
#define MCTP_ASPEED_CTRL_CMD_ECHO_LARGE 0x01
#define PCIE_TEST_BUFF_SIZE 2048
#define PCIE_TEST_TX_BUFF_SIZE (PCIE_TEST_BUFF_SIZE + sizeof(struct mctp_ctrl_msg_hdr))
#define PCIE_TEST_RX_BUFF_SIZE	(PCIE_TEST_BUFF_SIZE + sizeof(struct mctp_ctrl_msg_hdr) + 1)

#define REQUESTER_EID 8
#define RESPONDER_EID 9

struct mctp_ctrl_req {
	struct mctp_ctrl_msg_hdr hdr;
	uint8_t data[MCTP_BTU];
};

struct mctp_ctrl_resp {
	struct mctp_ctrl_msg_hdr hdr;
	uint8_t completion_code;
	uint8_t data[MCTP_BTU];
};

struct mctp_echo_resp {
	struct mctp_ctrl_msg_hdr hdr;
	uint8_t completion_code;
	uint8_t data[PCIE_TEST_BUFF_SIZE];
};

/* Test MCTP ctx */
struct test_mctp_ctx {
	struct mctp_binding *astpcie_binding;
	struct mctp *mctp;
	uint16_t len;
	void *rx_buf;
	void *port;
};

struct mctp_binding_astpcie {
	struct mctp_binding binding;
	uint16_t bdf;
	uint8_t medium_id;
	int fd;
};

void usage(FILE *fp, int argc, char **argv);
void print_raw_resp(uint8_t *rbuf, int rlen);
int compare_pattern(uint8_t *pattern0, uint8_t *pattern1, int size);
void test_pattern_prepare(uint8_t *pattern, int size);
void rx_response_handler(uint8_t eid, void *data, void *msg, size_t len,
			 bool tag_owner, uint8_t tag, void *prv);
void rx_request_handler(mctp_eid_t src, void *data, void *msg, size_t len,
			bool tag_owner, uint8_t tag, void *msg_binding_private);
void rx_request_control_handler(mctp_eid_t src, void *data, void *msg, size_t len,
				bool tag_owner, uint8_t tag, void *msg_binding_private);
void wait_for_request(struct test_mctp_ctx *ctx);
int test_mctp_astpcie_recv_data_timeout_raw(struct test_mctp_ctx *ctx, uint8_t dst, int TOsec);
struct test_mctp_ctx *test_mctp_astpcie_init(char *mctp_dev, uint8_t bus, uint8_t routing, uint8_t dst_dev, uint8_t dst_func,
					     uint8_t dst_eid, uint8_t src_eid);
int test_mctp_astpcie_send_data(struct test_mctp_ctx *ctx, uint8_t dst, uint8_t flag_tag,
				void *req, size_t size);
void test_mctp_astpcie_free(struct test_mctp_ctx *ctx);
int test_send_mctp_cmd(char *mctp_dev, uint8_t bus, uint8_t routing, uint8_t dst_dev, uint8_t dst_func, uint8_t dst_eid, uint8_t src_eid,
		       uint8_t *tbuf, int tlen, uint8_t *rbuf, int *rlen);
int test_mctp_astpcie_get_bdf(char *mctp_dev, uint8_t *src_bus, uint8_t *src_dev, uint8_t *src_func);
struct test_mctp_ctx *test_mctp_astpcie_init(char *mctp_dev, uint8_t bus, uint8_t routing, uint8_t dst_dev, uint8_t dst_func,
					     uint8_t dst_eid, uint8_t src_eid);
int test_mctp_fake_responder(char *mctp_dev, uint8_t bus, uint8_t routing, uint8_t dst_dev, uint8_t dst_func,
			     uint8_t dst_eid, uint8_t src_eid);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _MCTP_ASTPCIE_TEST_H_ */
