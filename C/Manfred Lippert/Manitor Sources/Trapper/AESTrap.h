#ifndef __Trapper_AESTrap_H__#define __Trapper_AESTrap_H__#include "TrapperDebug.h"#include <xbra.h>#include <AVLTree.h>#include <LinkedList.h>#include <trapper.h>#if COUNT_JUMPTABLE_USEextern int16 aes_debug_counter_max;#endifextern int16 AES_traced;			// Flag, ob AES grunds�tzlich getraced werden sollextern int16 AES_call_traced;	// Flag, ob vor AES-Aufrufen getraced werden sollextern int16 AES_return_traced;	// Flag, ob nach AES-Aufrufen getraced werden sollextern XBRA GEM_XBRA;extern int16 AES_insert_call(int16 opcode, AESCallFunc func);extern int16 AES_remove_call(int16 opcode, AESCallFunc func);extern int16 AES_insert_return(int16 opcode, AESReturnFunc func);extern int16 AES_remove_return(int16 opcode, AESReturnFunc func);/* Klasses for Call-Trace: */class AESCall : public Listable {	AESCallFunc func;	// eingeklinkte Routinepublic:	AESCall(AESCallFunc func) {this->func = func;};	void call(AESPB *para, int16 *call_original, int16 super_called) const {		func(para, call_original, super_called);	};	AESCall *get_next() const {return (AESCall *)Listable::get_next();};	AESCall *get_prev() const {return (AESCall *)Listable::get_prev();};	AESCallFunc get_func() const {return func;};};class AESCallKette : public LinkedList {public:	void insert(AESCall *glied, AESCall *pos = 0, int16 posdef = LINK_END) {		LinkedList::insert(glied, pos, posdef);	};	void remove(AESCall *glied) {LinkedList::remove(glied);};	void kill(AESCall *glied) {LinkedList::kill(glied);};	AESCall *get_first() const {return (AESCall *)LinkedList::get_first();};	AESCall *get_last() const {return (AESCall *)LinkedList::get_last();};};class AESCallsAVL : public AVL {	int16 opcode;			// AES-Call, in den sich diese Routinen eingeklinkt haben	AESCallKette calls;	// eingeklinkte Routinenpublic:	AESCallsAVL(int16 opcode) {this->opcode = opcode;};	int16 get_opcode() const {return opcode;};	AESCallKette *get_calls() {return &calls;};};#pragma warn_unusedarg offclass AESCallsAVLTree : public AVLTree {	int32 counter;public:	virtual int32 compare(AVL *a, AVL *b) const {return compare((AESCallsAVL *)a, (AESCallsAVL *)b);};	virtual int32 compare(AVL *a, int32 val) const {return compare((AESCallsAVL *)a, val);};	virtual int32 compare(AVL *a, void *ptr) const {return 0;};	int32 compare(AESCallsAVL *a, AESCallsAVL *b) const {		return (int32)(a->get_opcode() - b->get_opcode());	};	int32 compare(AESCallsAVL *a, int32 opcode) const {		return (int32)(a->get_opcode() - (int16)opcode);	};	void add_counter(int16 val);	void insert(AESCallsAVL *elem) {AVLTree::insert(elem); add_counter(1);};	void remove(AESCallsAVL *elem) {add_counter(-1); AVLTree::remove(elem);};	void kill(AESCallsAVL *elem) {add_counter(-1); AVLTree::kill(elem);};	AESCallsAVL *search(AESCallsAVL *elem) const {		return (AESCallsAVL *)AVLTree::search(elem);	};	AESCallsAVL *search(int16 opcode) const {		return (AESCallsAVL *)AVLTree::search((int32)opcode);	};};#pragma warn_unusedarg reset/* Klasses for Return-Trace: */class AESReturn : public Listable {	AESReturnFunc func;	// eingeklinkte Routinepublic:	AESReturn(AESReturnFunc func) {this->func = func;};	void call(AESPB *para, int16 is_super) const {		func(para, is_super);	};	AESReturn *get_next() const {return (AESReturn *)Listable::get_next();};	AESReturn *get_prev() const {return (AESReturn *)Listable::get_prev();};	AESReturnFunc get_func() const {return func;};};class AESReturnKette : public LinkedList {public:	void insert(AESReturn *glied, AESReturn *pos = 0, int16 posdef = LINK_END) {		LinkedList::insert(glied, pos, posdef);	};	void remove(AESReturn *glied) {LinkedList::remove(glied);};	void kill(AESReturn *glied) {LinkedList::kill(glied);};	AESReturn *get_first() const {return (AESReturn *)LinkedList::get_first();};	AESReturn *get_last() const {return (AESReturn *)LinkedList::get_last();};};class AESReturnsAVL : public AVL {	int16 opcode;			// AES-Return, in den sich diese Routinen eingeklinkt haben	AESReturnKette calls;	// eingeklinkte Routinenpublic:	AESReturnsAVL(int16 opcode) {this->opcode = opcode;};	int16 get_opcode() const {return opcode;};	AESReturnKette *get_calls() {return &calls;};};#pragma warn_unusedarg offclass AESReturnsAVLTree : public AVLTree {	int32 counter;public:	virtual int32 compare(AVL *a, AVL *b) const {return compare((AESReturnsAVL *)a, (AESReturnsAVL *)b);};	virtual int32 compare(AVL *a, int32 val) const {return compare((AESReturnsAVL *)a, val);};	virtual int32 compare(AVL *a, void *ptr) const {return 0;};	int32 compare(AESReturnsAVL *a, AESReturnsAVL *b) const {		return (int32)(a->get_opcode() - b->get_opcode());	};	int32 compare(AESReturnsAVL *a, int32 opcode) const {		return (int32)(a->get_opcode() - (int16)opcode);	};	void add_counter(int16 val);	void insert(AESReturnsAVL *elem) {AVLTree::insert(elem); add_counter(1);};	void remove(AESReturnsAVL *elem) {add_counter(-1); AVLTree::remove(elem);};	void kill(AESReturnsAVL *elem) {add_counter(-1); AVLTree::kill(elem);};	AESReturnsAVL *search(AESReturnsAVL *elem) const {		return (AESReturnsAVL *)AVLTree::search(elem);	};	AESReturnsAVL *search(int16 opcode) const {		return (AESReturnsAVL *)AVLTree::search((int32)opcode);	};};#pragma warn_unusedarg reset#endif