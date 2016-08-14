#include "stdafx.h"
#include "packet.h"
#include <primitives.h>
#include "win_helper.h"
#include "helpers.h"

using namespace std;

quasar_packet::quasar_packet() :
	m_id(PACKET_UNKNOWN),
	m_serializer(),
	m_deserializer(){
}

quasar_packet::quasar_packet(QuasarPacketId id) :
	m_id(id) {

}

QuasarPacketId quasar_packet::get_id() const {
	return m_id;
}

void quasar_packet::begin_serialization() {
	m_serializer.write_primitive(static_cast<uint32_t>(m_id));
}

void quasar_packet::finalize_serialization() {
	auto instance = m_serializer.get_serializer_instance();
	int32_t payloadSize = instance->size();
	char *chars = reinterpret_cast<char*>(&payloadSize);

	instance->insert(instance->begin(), chars, chars + sizeof(int32_t));
}

void quasar_packet::write_header(vector<unsigned char> &payloadBuf) const {
	primitives::write_varint32(payloadBuf, m_id);
}