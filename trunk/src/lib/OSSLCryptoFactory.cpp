/* $Id$ */

/*
 * Copyright (c) 2010 SURFnet bv
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*****************************************************************************
 OSSLCryptoFactory.cpp

 This is an OpenSSL based cryptographic algorithm factory
 *****************************************************************************/

#include "config.h"
#include "OSSLCryptoFactory.h"
#include "OSSLRNG.h"
#include "OSSLAES.h"

#include <algorithm>
#include <string.h>
#include <openssl/ssl.h>

// Initialise the one-and-only instance
OSSLCryptoFactory* OSSLCryptoFactory::instance = NULL;

// Constructor
OSSLCryptoFactory::OSSLCryptoFactory()
{
	// Initialise OpenSSL
	OpenSSL_add_all_algorithms();
}

// Return the one-and-only instance
OSSLCryptoFactory* OSSLCryptoFactory::i()
{
	if (instance == NULL)
	{
		instance = new OSSLCryptoFactory();
	}

	return instance;
}

// Create a concrete instance of a symmetric algorithm
SymmetricAlgorithm* OSSLCryptoFactory::getSymmetricAlgorithm(std::string algorithm)
{
	std::string lcAlgo;
	std::transform(algorithm.begin(), algorithm.end(), lcAlgo.begin(), tolower);

	if (!strcmp(lcAlgo.c_str(), "aes"))
	{
		return new OSSLAES();
	}
	else 
	{
		// No algorithm implementation is available
		ERROR_MSG("Unknown algorithm '%s'", lcAlgo.c_str());

		return NULL;
	}
}

// Create a concrete instance of an asymmetric algorithm
AsymmetricAlgorithm* OSSLCryptoFactory::getAsymmetricAlgorithm(std::string algorithm)
{
	std::string lcAlgo;
	std::transform(algorithm.begin(), algorithm.end(), lcAlgo.begin(), tolower);

	{
		// No algorithm implementation is available
		ERROR_MSG("Unknown algorithm '%s'", algorithm.c_str());

		return NULL;
	}
}

// Create a concrete instance of a hash algorithm
HashAlgorithm* OSSLCryptoFactory::getHashAlgorithm(std::string algorithm)
{
	// TODO: add algorithm implementations

	// No algorithm implementation is available
	return NULL;
}

// Create a concrete instance of an RNG
RNG* OSSLCryptoFactory::getRNG(std::string name /* = "default" */)
{
	if (name == "default")
	{
		return new OSSLRNG();
	}

	// No algorithm implementation is available
	return NULL;
}
