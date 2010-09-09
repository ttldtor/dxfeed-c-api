/*
* The contents of this file are subject to the Mozilla Public License Version
* 1.1 (the "License"); you may not use this file except in compliance with
* the License. You may obtain a copy of the License at
* http://www.mozilla.org/MPL/
*
* Software distributed under the License is distributed on an "AS IS" basis,
* WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
* for the specific language governing rights and limitations under the
* License.
*
* The Initial Developer of the Original Code is Devexperts LLC.
* Portions created by the Initial Developer are Copyright (C) 2010
* the Initial Developer. All Rights Reserved.
*
* Contributor(s):
*
*/

#include "DataStructures.h"
#include "ParserCommon.h"
#include "EventDataFieldSetters.h"
#include "DXAlgorithms.h"

/* -------------------------------------------------------------------------- */
/*
 *	Trade data fields
 */
/* -------------------------------------------------------------------------- */

static dx_field_info_t dx_fields_trade[] = { 
// 	{ dx_fid_utf_char, L"Last.Exchange", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_trade_t, last_exchange) },
// 	{ dx_fid_compact_int, L"Last.Time", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_trade_t, last_time) },
// 	{ dx_fid_compact_int | dx_fid_flag_decimal, L"Last.Price", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_trade_t, last_price) },
	{ dx_fid_compact_int, L"Last.Tick", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_trade_t, last_tick) },
	{ dx_fid_compact_int, L"Last.Size", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_trade_t, last_size) },
// 	{ dx_fid_compact_int | dx_fid_flag_decimal, L"Last.Change", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_trade_t, last_change) }, 
// 	{ dx_fid_compact_int | dx_fid_flag_decimal, L"Volume", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_trade_t, volume) }
}; 

/* -------------------------------------------------------------------------- */
/*
 *	Quote data fields
 */
/* -------------------------------------------------------------------------- */

static dx_field_info_t dx_fields_quote[] = {
    { dx_fid_utf_char, L"Bid.Exchange", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_quote_t, bid_exchange) },
    { dx_fid_compact_int | dx_fid_flag_decimal, L"Bid.Price", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_quote_t, bid_price) },
    { dx_fid_compact_int, L"Bid.Size", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_quote_t, bid_size) },
    { dx_fid_utf_char, L"Ask.Exchange", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_quote_t, ask_exchange) },
    { dx_fid_compact_int | dx_fid_flag_decimal, L"Ask.Price", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_quote_t, ask_price) },
    { dx_fid_compact_int, L"Ask.Size", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_quote_t, ask_size) },
    { dx_fid_compact_int, L"Bid.Time", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_quote_t, bid_time) },
    { dx_fid_compact_int, L"Ask.Time", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_quote_t, ask_time) }
};

/* -------------------------------------------------------------------------- */
/*
 *	Fundamental data fields
 */
/* -------------------------------------------------------------------------- */

static dx_field_info_t dx_fields_fundamental[] = { 
	{ dx_fid_compact_int | dx_fid_flag_decimal, L"High.Price", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_fundamental_t, high_price) },
	{ dx_fid_compact_int | dx_fid_flag_decimal, L"Low.Price", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_fundamental_t, low_price) },
	{ dx_fid_compact_int | dx_fid_flag_decimal, L"Open.Price", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_fundamental_t, open_price) },
	{ dx_fid_compact_int | dx_fid_flag_decimal, L"Close.Price", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_fundamental_t, close_price) },
	{ dx_fid_compact_int, L"OpenInterest", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_fundamental_t, open_interest) }
};
		
/* -------------------------------------------------------------------------- */
/*
 *	Profile data fields
 */
/* -------------------------------------------------------------------------- */

static dx_field_info_t dx_fields_profile[] = { 
	//{ dx_fid_compact_int | dx_fid_flag_decimal, L"Beta", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_profile_t, beta) },
// 	{ dx_fid_compact_int | dx_fid_flag_decimal, L"Eps", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_profile_t, eps) },
// 	{ dx_fid_compact_int, L"DivFreq", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_profile_t, div_freq) },
// 	//{ dx_fid_compact_int | dx_fid_flag_decimal, L"ExdDiv.Amount", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_profile_t, exd_div_amount) },
// 	//{ dx_fid_compact_int , L"ExdDiv.Date", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_profile_t, exd_div_date) },
// 	{ dx_fid_compact_int | dx_fid_flag_decimal, L"52High.Price", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_profile_t, price_52_high) },
// 	{ dx_fid_compact_int | dx_fid_flag_decimal, L"52Low.Price", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_profile_t, price_52_low) },
// 	{ dx_fid_compact_int | dx_fid_flag_decimal, L"Shares", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_profile_t, shares) },
// 	{ dx_fid_compact_int, L"IsIndex", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_profile_t, is_index) },
 	{ dx_fid_utf_char_array, L"Description", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_profile_t, description) }
	//{ dx_fid_utf_char_array, L"DescriptionDDSSDDSS", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_profile_t, description) }
}; 

/* -------------------------------------------------------------------------- */
/*
 *	Market maker data fields
 */
/* -------------------------------------------------------------------------- */

static dx_field_info_t dx_fields_market_maker[] = { 
	{ dx_fid_utf_char, L"MMExchange", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_market_maker, mm_exchange) },
	{ dx_fid_compact_int, L"MMID", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_market_maker, mm_id) },
	{ dx_fid_compact_int | dx_fid_flag_decimal, L"MMBid.Price", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_market_maker, mmbid_price) },
	{ dx_fid_compact_int, L"MMBid.Size", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_market_maker, mmbid_size) },
	{ dx_fid_compact_int | dx_fid_flag_decimal, L"MMAsk.Price", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_market_maker, mmask_price) },
	{ dx_fid_compact_int, L"MMAsk.Size", DX_EVENT_DATA_FIELD_SETTER_NAME(dxf_market_maker, mmask_size) }
}; 

/* -------------------------------------------------------------------------- */
/*
 *	Event data records
 */
/* -------------------------------------------------------------------------- */

static const dx_record_info_t g_event_records[] = {
	{ L"Trade", sizeof(dx_fields_trade) / sizeof(dx_fields_trade[0]), &dx_fields_trade[0] },
    { L"Quote", sizeof(dx_fields_quote) / sizeof(dx_fields_quote[0]), &dx_fields_quote[0] },
    { L"Fundamental", sizeof(dx_fields_fundamental) / sizeof(dx_fields_fundamental[0]), &dx_fields_fundamental[0] },
    { L"Profile", sizeof(dx_fields_profile) / sizeof(dx_fields_profile[0]), &dx_fields_profile[0] },
    { L"MarketMaker", sizeof(dx_fields_market_maker) / sizeof(dx_fields_market_maker[0]), &dx_fields_market_maker[0] },
};

static dx_event_id_t g_protocol_to_event_id_map[dx_eid_count] = {
    dx_eid_trade,
    dx_eid_quote,
    dx_eid_fundamental,
    dx_eid_profile,
    dx_eid_market_maker
};

static bool g_record_description_states[dx_eid_count] = { 0 };

/* -------------------------------------------------------------------------- */
/*
 *	Auxiliary functions
 */
/* -------------------------------------------------------------------------- */

void dx_swap_record_fields (dx_field_info_t* f1, dx_field_info_t* f2) {
    DX_SWAP(int, f1->type, f2->type);
    DX_SWAP(dx_const_string_t, f1->name, f2->name);
    DX_SWAP(dx_event_data_field_setter_t, f1->setter, f2->setter);
}

/* -------------------------------------------------------------------------- */
/*
 *	Event record functions implementation
 */
/* -------------------------------------------------------------------------- */

dx_event_id_t dx_get_event_id (dx_int_t protocol_id) {
    return g_protocol_to_event_id_map[protocol_id];
}

/* -------------------------------------------------------------------------- */

void dx_assign_event_protocol_id (dx_event_id_t event_id, dx_int_t protocol_id) {
    g_protocol_to_event_id_map[protocol_id] = event_id;
}

/* -------------------------------------------------------------------------- */

const dx_record_info_t* dx_get_event_record_by_id (dx_event_id_t event_id) {
	return &g_event_records[event_id];
}

/* -------------------------------------------------------------------------- */

dx_event_id_t dx_get_event_record_id_by_name (dx_const_string_t record_name) {
    dx_event_id_t event_id = dx_eid_begin;

    for (; event_id < dx_eid_count; ++event_id) {
        if (wcscmp(g_event_records[event_id].name, record_name) == 0) {
            return event_id;
        }
    }
    
    return dx_eid_invalid;
}

/* -------------------------------------------------------------------------- */

bool dx_move_record_field (const dx_record_info_t* record_info, dx_const_string_t field_name,
                           dx_int_t field_type, size_t field_index) {
    size_t cur_field_index = 0;
    dx_field_info_t* fields = (dx_field_info_t*)record_info->fields;
    
    for (; cur_field_index < record_info->field_count; ++cur_field_index) {
        if (wcscmp(fields[cur_field_index].name, field_name) == 0 &&
            fields[cur_field_index].type == field_type) {
            
            if (cur_field_index != field_index) {
                dx_swap_record_fields(fields + cur_field_index, fields + field_index);
            }
            
            return true;
        }
    }
    
    return false;
}

/* -------------------------------------------------------------------------- */

void dx_clear_record_description_state (void) {
    dx_event_id_t eid = dx_eid_begin;
    
    for (; eid < dx_eid_count; ++eid) {
        g_record_description_states[eid] = false;
    }
}

/* -------------------------------------------------------------------------- */

void dx_set_record_description_state (dx_event_id_t event_id) {
    g_record_description_states[event_id] = true;
}

/* -------------------------------------------------------------------------- */

bool dx_get_record_description_state (dx_event_id_t event_id) {
    return g_record_description_states[event_id];
}