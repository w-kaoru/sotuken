#pragma once
/*!
 * @brief	NoncopyÉ|ÉäÉVÅ[
 */

#ifndef _TKNONCOPYABLE_H_
#define _TKNONCOPYABLE_H_

struct NoncCopyable {
	NoncCopyable() = default;
	NoncCopyable(const NoncCopyable&) = delete;
	NoncCopyable& operator=(const NoncCopyable&) = delete;
};

#endif // _TKNONCOPYABLE_H_