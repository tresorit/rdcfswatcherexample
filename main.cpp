/*
    BSD 3-Clause License
    
    Copyright (c) 2020, Tresorit Kft.
    All rights reserved.
    
    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    
    * Redistributions of source code must retain the above copyright notice, this
      list of conditions and the following disclaimer.
    
    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.
    
    * Neither the name of the copyright holder nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.
    
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <iostream>
#include <cstdio>
#include <string>

#include "rdc_fs_watcher.h"

int wmain(int argc, wchar_t** argv)
{
	if (argc == 1) {
		std::wcout << L"Supply paths to listen changes for." << std::endl;
		return 1;
	}

	RdcFSWatcher watch;
	watch.changeEvent = [](int64_t id, const std::set<std::pair<std::wstring, uint32_t>>& notifications) {
		for (const auto& notif : notifications) {
			std::wcout << L"Change on watcher with ID=" << id
				<< L", relative path: \"" << notif.first.c_str() << L"\""
				L"event: " << std::to_wstring(notif.second).c_str() << std::endl;
		}
	};
	watch.errorEvent = [](int64_t id) {
		std::wcout << L"An error has occurred, no further events will be sent for ID= " << id << std::endl;
	};
	std::wcout << L"Listening for changes on the following directories:\n";
	for (int i = 1; i < argc; ++i) {
		bool result = watch.addDirectory(i, argv[i]);
		if (result) {
			std::wcout << L"Listening for changes (ID=" << i << L") on: ";
		}
		else {
			std::wcout << L"Failed to listen for changes on: ";
		}
		std::wcout << argv[i] << std::endl;
	}
	std::getchar();
}
