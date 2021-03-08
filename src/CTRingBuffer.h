/*
 * CTRingBuffer.h
 *
 *  Created on: Mar 8, 2021
 *      Author: reza
 */

#ifndef CTRINGBUFFER_H_
#define CTRINGBUFFER_H_

enum error_t{BUFFERFULL, BUFFEREMPTY};

#define DEFAULTRINGBUFFERSIZE 10

template <class DATA>
class CTRingBuffer {
private:
	DATA* m_data;
	unsigned int m_size;
	unsigned int m_filled;
	unsigned int m_writeIdx;
	unsigned int m_readIdx;
public:
	typedef DATA iterator;
	CTRingBuffer(unsigned int size = DEFAULTRINGBUFFERSIZE);
	bool put(const DATA element);
	bool get(DATA& element);
	CTRingBuffer<DATA>& operator=(const CTRingBuffer<DATA>& other);
	bool operator +=(const DATA& element);
	DATA operator *();
	unsigned int first();
	unsigned int last();
	void clear();
	void setSize(unsigned int size);
	virtual ~CTRingBuffer();
};

template<class DATA>
inline CTRingBuffer<DATA>::CTRingBuffer(unsigned int size) {
	if (size == 0)
	{
	size = 5;
	}
	m_size = size;
	m_filled = 0;
	m_readIdx = 0;
	m_writeIdx = 0;
	m_data = new DATA[m_size];
	for(unsigned int i=0; i < m_size; i++){
		m_data[i] = DATA();
	}
}

template<class DATA>
inline bool CTRingBuffer<DATA>::put(const DATA element) {
	bool result = false;
	if(m_filled < m_size){
		m_data[(m_writeIdx++) % m_size] = element;
		m_filled++;
		result = true;
	}
	else{
		result = false;
		throw error_t::BUFFERFULL;
	}
	return result;
}

template<class DATA>
inline bool CTRingBuffer<DATA>::get(DATA &element) {
	bool result = false;
	if(m_filled > 0){
		element = m_data[m_readIdx++];
		m_readIdx %= m_size;
		m_filled--;
		result = true;
	}
	else{
		result = false;
		throw error_t::BUFFEREMPTY;
	}
	return result;
}

template<class DATA>
inline CTRingBuffer<DATA>& CTRingBuffer<DATA>::operator =(const CTRingBuffer<DATA> &other) {
	m_size = other.m_size;
	m_filled = other.m_filled;
	m_readIdx = other.m_readIdx;
	m_writeIdx = other.m_writeIdx;
	m_data = new DATA[m_size];
	for(unsigned int i=0; i < m_size; i++){
		m_data[i] = other.m_data[i];
	}
}

template<class DATA>
inline bool CTRingBuffer<DATA>::operator +=(const DATA &element) {
	bool result = false;
	if(m_filled < m_size){
		m_data[m_writeIdx++] = element;
		m_writeIdx %= m_size;
		m_filled++;
		result = true;
	}
	else{
		result = false;
		throw error_t::BUFFERFULL;
	}
	return result;
}

template<class DATA>
inline DATA CTRingBuffer<DATA>::operator *() {
	if (m_filled > 0)
	{
	m_filled--;
	return m_data[(m_readIdx++) % m_size];
	}
	else
	{
	throw BUFFEREMPTY;
	}
	return 0; //will never be reached
}

template<class DATA>
inline unsigned int CTRingBuffer<DATA>::first() {
	return m_readIdx;
}

template<class DATA>
inline unsigned int CTRingBuffer<DATA>::last() {
	if (m_writeIdx > m_readIdx)
	{
	return m_writeIdx;
	}
	else
	{
	return m_size + m_writeIdx - m_readIdx ;
	}
}

template<class DATA>
inline void CTRingBuffer<DATA>::clear() {
	m_filled = 0;
	m_readIdx = 0;
	m_writeIdx = 0;
	for(unsigned int i=0; i < m_size; i++){
		m_data[i] = DATA();
	}
}

template<class DATA>
inline void CTRingBuffer<DATA>::setSize(unsigned int size) {
	m_size = size;
}

template<class DATA>
inline CTRingBuffer<DATA>::~CTRingBuffer() {
	delete [] m_data;
}

#endif /* CTRINGBUFFER_H_ */
