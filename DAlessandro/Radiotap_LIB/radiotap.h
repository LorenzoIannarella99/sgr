/*
 * Copyright (c) 2017		Intel Deutschland GmbH
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#ifndef __RADIOTAP_H
#define __RADIOTAP_H

#if defined(__APPLE__)
#include <libkern/OSByteOrder.h>
#define bswap_16 OSSwapInt16
#define bswap_32 OSSwapInt32
#define bswap_64 OSSwapInt64
#include <machine/endian.h>
#define le16toh(x) OSSwapLittleToHostInt16(x)
#define le32toh(x) OSSwapLittleToHostInt32(x)
#define le64toh(x) OSSwapLittleToHostInt64(x)
#endif

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;


/**
 * struct ieee82011_radiotap_header - base radiotap header
 */
struct ieee80211_radiotap_header {
	/**
	 * @it_version: radiotap version, always 0
	 */
	uint8_t it_version;

	/**
	 * @it_pad: padding (or alignment)
	 */
	uint8_t it_pad;

	/**
	 * @it_len: overall radiotap header length
	 */
	uint16_t it_len;

	/**
	 * @it_present: (first) present word
	 */
	uint32_t it_present;
} __attribute__((__packed__));

/* version is always 0 */
#define PKTHDR_RADIOTAP_VERSION	0

/* see the radiotap website for the descriptions */
enum ieee80211_radiotap_presence {
	IEEE80211_RADIOTAP_TSFT = 0,
	IEEE80211_RADIOTAP_FLAGS = 1,
	IEEE80211_RADIOTAP_RATE = 2,
	IEEE80211_RADIOTAP_CHANNEL = 3,
	IEEE80211_RADIOTAP_FHSS = 4,
	IEEE80211_RADIOTAP_DBM_ANTSIGNAL = 5,
	IEEE80211_RADIOTAP_DBM_ANTNOISE = 6,
	IEEE80211_RADIOTAP_LOCK_QUALITY = 7,
	IEEE80211_RADIOTAP_TX_ATTENUATION = 8,
	IEEE80211_RADIOTAP_DB_TX_ATTENUATION = 9,
	IEEE80211_RADIOTAP_DBM_TX_POWER = 10,
	IEEE80211_RADIOTAP_ANTENNA = 11,
	IEEE80211_RADIOTAP_DB_ANTSIGNAL = 12,
	IEEE80211_RADIOTAP_DB_ANTNOISE = 13,
	IEEE80211_RADIOTAP_RX_FLAGS = 14,
	IEEE80211_RADIOTAP_TX_FLAGS = 15,
	IEEE80211_RADIOTAP_RTS_RETRIES = 16,
	IEEE80211_RADIOTAP_DATA_RETRIES = 17,
	/* 18 is XChannel, but it's not defined yet */
	IEEE80211_RADIOTAP_MCS = 19,
	IEEE80211_RADIOTAP_AMPDU_STATUS = 20,
	IEEE80211_RADIOTAP_VHT = 21,
	IEEE80211_RADIOTAP_TIMESTAMP = 22,

	/* valid in every it_present bitmap, even vendor namespaces */
	IEEE80211_RADIOTAP_RADIOTAP_NAMESPACE = 29,
	IEEE80211_RADIOTAP_VENDOR_NAMESPACE = 30,
	IEEE80211_RADIOTAP_EXT = 31
};

/* for IEEE80211_RADIOTAP_FLAGS */
enum ieee80211_radiotap_flags {
	IEEE80211_RADIOTAP_F_CFP = 0x01,
	IEEE80211_RADIOTAP_F_SHORTPRE = 0x02,
	IEEE80211_RADIOTAP_F_WEP = 0x04,
	IEEE80211_RADIOTAP_F_FRAG = 0x08,
	IEEE80211_RADIOTAP_F_FCS = 0x10,
	IEEE80211_RADIOTAP_F_DATAPAD = 0x20,
	IEEE80211_RADIOTAP_F_BADFCS = 0x40,
};

/* for IEEE80211_RADIOTAP_CHANNEL */
enum ieee80211_radiotap_channel_flags {
	IEEE80211_CHAN_CCK = 0x0020,
	IEEE80211_CHAN_OFDM = 0x0040,
	IEEE80211_CHAN_2GHZ = 0x0080,
	IEEE80211_CHAN_5GHZ = 0x0100,
	IEEE80211_CHAN_DYN = 0x0400,
	IEEE80211_CHAN_HALF = 0x4000,
	IEEE80211_CHAN_QUARTER = 0x8000,
};

/* for IEEE80211_RADIOTAP_RX_FLAGS */
enum ieee80211_radiotap_rx_flags {
	IEEE80211_RADIOTAP_F_RX_BADPLCP = 0x0002,
};

/* for IEEE80211_RADIOTAP_TX_FLAGS */
enum ieee80211_radiotap_tx_flags {
	IEEE80211_RADIOTAP_F_TX_FAIL = 0x0001,
	IEEE80211_RADIOTAP_F_TX_CTS = 0x0002,
	IEEE80211_RADIOTAP_F_TX_RTS = 0x0004,
	IEEE80211_RADIOTAP_F_TX_NOACK = 0x0008,
};

/* for IEEE80211_RADIOTAP_MCS "have" flags */
enum ieee80211_radiotap_mcs_have {
	IEEE80211_RADIOTAP_MCS_HAVE_BW = 0x01,
	IEEE80211_RADIOTAP_MCS_HAVE_MCS = 0x02,
	IEEE80211_RADIOTAP_MCS_HAVE_GI = 0x04,
	IEEE80211_RADIOTAP_MCS_HAVE_FMT = 0x08,
	IEEE80211_RADIOTAP_MCS_HAVE_FEC = 0x10,
	IEEE80211_RADIOTAP_MCS_HAVE_STBC = 0x20,
};

enum ieee80211_radiotap_mcs_flags {
	IEEE80211_RADIOTAP_MCS_BW_MASK = 0x03,
	IEEE80211_RADIOTAP_MCS_BW_20 = 0,
	IEEE80211_RADIOTAP_MCS_BW_40 = 1,
	IEEE80211_RADIOTAP_MCS_BW_20L = 2,
	IEEE80211_RADIOTAP_MCS_BW_20U = 3,

	IEEE80211_RADIOTAP_MCS_SGI = 0x04,
	IEEE80211_RADIOTAP_MCS_FMT_GF = 0x08,
	IEEE80211_RADIOTAP_MCS_FEC_LDPC = 0x10,
	IEEE80211_RADIOTAP_MCS_STBC_MASK = 0x60,
	IEEE80211_RADIOTAP_MCS_STBC_1 = 1,
	IEEE80211_RADIOTAP_MCS_STBC_2 = 2,
	IEEE80211_RADIOTAP_MCS_STBC_3 = 3,
	IEEE80211_RADIOTAP_MCS_STBC_SHIFT = 5,
};

/* for IEEE80211_RADIOTAP_AMPDU_STATUS */
enum ieee80211_radiotap_ampdu_flags {
	IEEE80211_RADIOTAP_AMPDU_REPORT_ZEROLEN = 0x0001,
	IEEE80211_RADIOTAP_AMPDU_IS_ZEROLEN = 0x0002,
	IEEE80211_RADIOTAP_AMPDU_LAST_KNOWN = 0x0004,
	IEEE80211_RADIOTAP_AMPDU_IS_LAST = 0x0008,
	IEEE80211_RADIOTAP_AMPDU_DELIM_CRC_ERR = 0x0010,
	IEEE80211_RADIOTAP_AMPDU_DELIM_CRC_KNOWN = 0x0020,
};

/* for IEEE80211_RADIOTAP_VHT */
enum ieee80211_radiotap_vht_known {
	IEEE80211_RADIOTAP_VHT_KNOWN_STBC = 0x0001,
	IEEE80211_RADIOTAP_VHT_KNOWN_TXOP_PS_NA = 0x0002,
	IEEE80211_RADIOTAP_VHT_KNOWN_GI = 0x0004,
	IEEE80211_RADIOTAP_VHT_KNOWN_SGI_NSYM_DIS = 0x0008,
	IEEE80211_RADIOTAP_VHT_KNOWN_LDPC_EXTRA_OFDM_SYM = 0x0010,
	IEEE80211_RADIOTAP_VHT_KNOWN_BEAMFORMED = 0x0020,
	IEEE80211_RADIOTAP_VHT_KNOWN_BANDWIDTH = 0x0040,
	IEEE80211_RADIOTAP_VHT_KNOWN_GROUP_ID = 0x0080,
	IEEE80211_RADIOTAP_VHT_KNOWN_PARTIAL_AID = 0x0100,
};

enum ieee80211_radiotap_vht_flags {
	IEEE80211_RADIOTAP_VHT_FLAG_STBC = 0x01,
	IEEE80211_RADIOTAP_VHT_FLAG_TXOP_PS_NA = 0x02,
	IEEE80211_RADIOTAP_VHT_FLAG_SGI = 0x04,
	IEEE80211_RADIOTAP_VHT_FLAG_SGI_NSYM_M10_9 = 0x08,
	IEEE80211_RADIOTAP_VHT_FLAG_LDPC_EXTRA_OFDM_SYM = 0x10,
	IEEE80211_RADIOTAP_VHT_FLAG_BEAMFORMED = 0x20,
};

enum ieee80211_radiotap_vht_coding {
	IEEE80211_RADIOTAP_CODING_LDPC_USER0 = 0x01,
	IEEE80211_RADIOTAP_CODING_LDPC_USER1 = 0x02,
	IEEE80211_RADIOTAP_CODING_LDPC_USER2 = 0x04,
	IEEE80211_RADIOTAP_CODING_LDPC_USER3 = 0x08,
};

/* for IEEE80211_RADIOTAP_TIMESTAMP */
enum ieee80211_radiotap_timestamp_unit_spos {
	IEEE80211_RADIOTAP_TIMESTAMP_UNIT_MASK = 0x000F,
	IEEE80211_RADIOTAP_TIMESTAMP_UNIT_MS = 0x0000,
	IEEE80211_RADIOTAP_TIMESTAMP_UNIT_US = 0x0001,
	IEEE80211_RADIOTAP_TIMESTAMP_UNIT_NS = 0x0003,
	IEEE80211_RADIOTAP_TIMESTAMP_SPOS_MASK = 0x00F0,
	IEEE80211_RADIOTAP_TIMESTAMP_SPOS_BEGIN_MDPU = 0x0000,
	IEEE80211_RADIOTAP_TIMESTAMP_SPOS_PLCP_SIG_ACQ = 0x0010,
	IEEE80211_RADIOTAP_TIMESTAMP_SPOS_EO_PPDU = 0x0020,
	IEEE80211_RADIOTAP_TIMESTAMP_SPOS_EO_MPDU = 0x0030,
	IEEE80211_RADIOTAP_TIMESTAMP_SPOS_UNKNOWN = 0x00F0,
};

enum ieee80211_radiotap_timestamp_flags {
	IEEE80211_RADIOTAP_TIMESTAMP_FLAG_64BIT = 0x00,
	IEEE80211_RADIOTAP_TIMESTAMP_FLAG_32BIT = 0x01,
	IEEE80211_RADIOTAP_TIMESTAMP_FLAG_ACCURACY = 0x02,
};

#endif /* __RADIOTAP_H */
