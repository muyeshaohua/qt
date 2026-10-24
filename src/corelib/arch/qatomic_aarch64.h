/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage:
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information: ensure the GNU Lesser General Public License
** requirements are met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file. Please review the following information: ensure
** the GNU General Public License version 3.0 requirements are met:
** http://www.gnu.org/copyleft/gpl.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QATOMIC_AARCH64_H
#define QATOMIC_AARCH64_H

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

#define Q_ATOMIC_INT_REFERENCE_COUNTING_IS_ALWAYS_NATIVE

inline bool QBasicAtomicInt::isReferenceCountingNative()
{ return true; }
inline bool QBasicAtomicInt::isReferenceCountingWaitFree()
{ return false; }

#define Q_ATOMIC_INT_TEST_AND_SET_IS_ALWAYS_NATIVE

inline bool QBasicAtomicInt::isTestAndSetNative()
{ return true; }
inline bool QBasicAtomicInt::isTestAndSetWaitFree()
{ return false; }

#define Q_ATOMIC_INT_FETCH_AND_STORE_IS_ALWAYS_NATIVE

inline bool QBasicAtomicInt::isFetchAndStoreNative()
{ return true; }
inline bool QBasicAtomicInt::isFetchAndStoreWaitFree()
{ return false; }

#define Q_ATOMIC_INT_FETCH_AND_ADD_IS_ALWAYS_NATIVE

inline bool QBasicAtomicInt::isFetchAndAddNative()
{ return true; }
inline bool QBasicAtomicInt::isFetchAndAddWaitFree()
{ return false; }

#define Q_ATOMIC_POINTER_TEST_AND_SET_IS_ALWAYS_NATIVE

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::isTestAndSetNative()
{ return true; }
template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::isTestAndSetWaitFree()
{ return false; }

#define Q_ATOMIC_POINTER_FETCH_AND_STORE_IS_ALWAYS_NATIVE

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::isFetchAndStoreNative()
{ return true; }
template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::isFetchAndStoreWaitFree()
{ return false; }

#define Q_ATOMIC_POINTER_FETCH_AND_ADD_IS_ALWAYS_NATIVE

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::isFetchAndAddNative()
{ return true; }
template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::isFetchAndAddWaitFree()
{ return false; }

// Implemented with the compiler builtins (__atomic_*): no hand-written
// assembly, correct memory ordering, and maintained by the compiler.

inline bool QBasicAtomicInt::ref()
{
    return __atomic_add_fetch(&_q_value, 1, __ATOMIC_RELAXED) != 0;
}

inline bool QBasicAtomicInt::deref()
{
    return __atomic_sub_fetch(&_q_value, 1, __ATOMIC_ACQ_REL) != 0;
}

inline bool QBasicAtomicInt::testAndSetOrdered(int expectedValue, int newValue)
{
    int expectedValue_ = expectedValue;
    return __atomic_compare_exchange_n(&_q_value, &expectedValue_, newValue,
                                       false, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE);
}

inline int QBasicAtomicInt::fetchAndStoreOrdered(int newValue)
{
    return __atomic_exchange_n(&_q_value, newValue, __ATOMIC_ACQ_REL);
}

inline int QBasicAtomicInt::fetchAndAddOrdered(int valueToAdd)
{
    return __atomic_fetch_add(&_q_value, valueToAdd, __ATOMIC_ACQ_REL);
}

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::testAndSetOrdered(T *expectedValue, T *newValue)
{
    T *expectedValue_ = expectedValue;
    return __atomic_compare_exchange_n(&_q_value, &expectedValue_, newValue,
                                       false, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE);
}

template <typename T>
Q_INLINE_TEMPLATE T *QBasicAtomicPointer<T>::fetchAndStoreOrdered(T *newValue)
{
    return __atomic_exchange_n(&_q_value, newValue, __ATOMIC_ACQ_REL);
}

template <typename T>
Q_INLINE_TEMPLATE T *QBasicAtomicPointer<T>::fetchAndAddOrdered(qptrdiff valueToAdd)
{
    return __atomic_fetch_add(&_q_value, valueToAdd * sizeof(T), __ATOMIC_ACQ_REL);
}

inline bool QBasicAtomicInt::testAndSetRelaxed(int expectedValue, int newValue)
{
    int expectedValue_ = expectedValue;
    return __atomic_compare_exchange_n(&_q_value, &expectedValue_, newValue,
                                       false, __ATOMIC_RELAXED, __ATOMIC_RELAXED);
}

inline bool QBasicAtomicInt::testAndSetAcquire(int expectedValue, int newValue)
{
    int expectedValue_ = expectedValue;
    return __atomic_compare_exchange_n(&_q_value, &expectedValue_, newValue,
                                       false, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE);
}

inline bool QBasicAtomicInt::testAndSetRelease(int expectedValue, int newValue)
{
    int expectedValue_ = expectedValue;
    return __atomic_compare_exchange_n(&_q_value, &expectedValue_, newValue,
                                       false, __ATOMIC_RELEASE, __ATOMIC_RELAXED);
}

inline int QBasicAtomicInt::fetchAndStoreRelaxed(int newValue)
{
    return __atomic_exchange_n(&_q_value, newValue, __ATOMIC_RELAXED);
}

inline int QBasicAtomicInt::fetchAndStoreAcquire(int newValue)
{
    return __atomic_exchange_n(&_q_value, newValue, __ATOMIC_ACQUIRE);
}

inline int QBasicAtomicInt::fetchAndStoreRelease(int newValue)
{
    return __atomic_exchange_n(&_q_value, newValue, __ATOMIC_RELEASE);
}

inline int QBasicAtomicInt::fetchAndAddRelaxed(int valueToAdd)
{
    return __atomic_fetch_add(&_q_value, valueToAdd, __ATOMIC_RELAXED);
}

inline int QBasicAtomicInt::fetchAndAddAcquire(int valueToAdd)
{
    return __atomic_fetch_add(&_q_value, valueToAdd, __ATOMIC_ACQUIRE);
}

inline int QBasicAtomicInt::fetchAndAddRelease(int valueToAdd)
{
    return __atomic_fetch_add(&_q_value, valueToAdd, __ATOMIC_RELEASE);
}

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::testAndSetRelaxed(T *expectedValue, T *newValue)
{
    T *expectedValue_ = expectedValue;
    return __atomic_compare_exchange_n(&_q_value, &expectedValue_, newValue,
                                       false, __ATOMIC_RELAXED, __ATOMIC_RELAXED);
}

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::testAndSetAcquire(T *expectedValue, T *newValue)
{
    T *expectedValue_ = expectedValue;
    return __atomic_compare_exchange_n(&_q_value, &expectedValue_, newValue,
                                       false, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE);
}

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::testAndSetRelease(T *expectedValue, T *newValue)
{
    T *expectedValue_ = expectedValue;
    return __atomic_compare_exchange_n(&_q_value, &expectedValue_, newValue,
                                       false, __ATOMIC_RELEASE, __ATOMIC_RELAXED);
}

template <typename T>
Q_INLINE_TEMPLATE T *QBasicAtomicPointer<T>::fetchAndStoreRelaxed(T *newValue)
{
    return __atomic_exchange_n(&_q_value, newValue, __ATOMIC_RELAXED);
}

template <typename T>
Q_INLINE_TEMPLATE T *QBasicAtomicPointer<T>::fetchAndStoreAcquire(T *newValue)
{
    return __atomic_exchange_n(&_q_value, newValue, __ATOMIC_ACQUIRE);
}

template <typename T>
Q_INLINE_TEMPLATE T *QBasicAtomicPointer<T>::fetchAndStoreRelease(T *newValue)
{
    return __atomic_exchange_n(&_q_value, newValue, __ATOMIC_RELEASE);
}

template <typename T>
Q_INLINE_TEMPLATE T *QBasicAtomicPointer<T>::fetchAndAddRelaxed(qptrdiff valueToAdd)
{
    return __atomic_fetch_add(&_q_value, valueToAdd * sizeof(T), __ATOMIC_RELAXED);
}

template <typename T>
Q_INLINE_TEMPLATE T *QBasicAtomicPointer<T>::fetchAndAddAcquire(qptrdiff valueToAdd)
{
    return __atomic_fetch_add(&_q_value, valueToAdd * sizeof(T), __ATOMIC_ACQUIRE);
}

template <typename T>
Q_INLINE_TEMPLATE T *QBasicAtomicPointer<T>::fetchAndAddRelease(qptrdiff valueToAdd)
{
    return __atomic_fetch_add(&_q_value, valueToAdd * sizeof(T), __ATOMIC_RELEASE);
}

QT_END_NAMESPACE

QT_END_HEADER

#endif // QATOMIC_AARCH64_H
