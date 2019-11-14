#pragma once
/*!
 * @brief	NoncopyÉ|ÉäÉVÅ[
 */

#ifndef _TKNONCOPYABLE_H_
#define _TKNONCOPYABLE_H_

struct NonCopyable {
	NonCopyable() = default;
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;
};

#endif // _TKNONCOPYABLE_H_