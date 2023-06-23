/*!
 * \file           sbgConfig.h
 * \author         SBG Systems (Raphael Siryani)
 * \date           17 March 2015
 *
 * \brief          Header file used to configure the framework.
 *
 * You can configure for example the logging system.
 *
 * \copyright		Copyright (C) 2022, SBG Systems SAS. All rights reserved.
 * \beginlicense	The MIT license
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * \endlicense
 */

#ifndef SBG_CONFIG_H
#define SBG_CONFIG_H

//----------------------------------------------------------------------//
//- Platform configuration                                             -//
//----------------------------------------------------------------------//

/*!
 * Windows x86 & x64 support both aligned and unaligned access
 */
#define SBG_CONFIG_UNALIGNED_ACCESS_AUTH			(0)

/*!
 * Windows is using little endianess
 */
#define SBG_CONFIG_BIG_ENDIAN						(0)

//----------------------------------------------------------------------//
//- Logging configuration                                              -//
//----------------------------------------------------------------------//

/*!
 * Enable all error logs
 * Default: Enabled
 */
#define SBG_CONFIG_ENABLE_LOG_ERROR					(1)
#define SBG_CONFIG_ENABLE_LOG_WARNING				(1)
#define SBG_CONFIG_ENABLE_LOG_INFO					(1)
#define SBG_CONFIG_ENABLE_LOG_DEBUG					(1)

#define SUPPRESS_SBG_WARNING

#endif	// SBG_CONFIG_H
