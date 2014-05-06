/*
#include "_STM.h"
#include "main.h"

#pragma comment(lib,"setupapi.lib")
#pragma comment(lib,"hid.lib")

	DWORD								ActualBytesRead2;
	DWORD								BytesRead2;
	HIDP_CAPS							Capabilities2;
	DWORD								cbBytesRead2;
	PSP_DEVICE_INTERFACE_DETAIL_DATA	detailData2;
	HANDLE								DeviceHandle2;
	DWORD								dwError2;
	char								FeatureReport2[256];
	HANDLE								hEventObject2;
	HANDLE								hDevInfo2;
	GUID								HidGuid2;
	OVERLAPPED							HIDOverlapped2;
	char								InputReport2[256];
	ULONG								Length2;
	LPOVERLAPPED						lpOverLap2;
	bool								MyDeviceDetected2 = FALSE; 
	char								MyDevicePathName2[50];
	DWORD								NumberOfBytesRead2;
	char								OutputReport2[256];
	HANDLE								ReadHandle2;
	DWORD								ReportType2;
	ULONG								Required2;
	char								ValueToDisplay2[50];
	HANDLE								WriteHandle2;


	int VendorID2 = 0x0477;
	int ProductID2 = 0x5620;

bool FindTheHID2()
{

	HIDD_ATTRIBUTES						Attributes;
	DWORD								DeviceUsage;
	SP_DEVICE_INTERFACE_DATA			devInfoData;
	bool								LastDevice = FALSE;
	//int									MemberIndex;
	LONG								Result;	
	char								UsageDescription[50];

	Length2 = 0;
	detailData2 = NULL;
	DeviceHandle2=NULL;

	HidD_GetHidGuid(&HidGuid2);	
	
	hDevInfo2=SetupDiGetClassDevs 
		(&HidGuid2, 
		NULL, 
		NULL, 
		DIGCF_PRESENT|DIGCF_INTERFACEDEVICE);
		
	devInfoData.cbSize = sizeof(devInfoData);


	//MemberIndex = 0;
	LastDevice = FALSE;

	do
	{

		Result=SetupDiEnumDeviceInterfaces 
			(hDevInfo2, 
			0, 
			&HidGuid2, 
			MemberIndex, 
			&devInfoData);

		if (Result != 0)
		{

			Result = SetupDiGetDeviceInterfaceDetail 
				(hDevInfo2, 
				&devInfoData, 
				NULL, 
				0, 
				&Length2, 
				NULL);

			detailData2 = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(Length2);
			

			detailData2 -> cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);


			Result = SetupDiGetDeviceInterfaceDetail 
				(hDevInfo2, 
				&devInfoData, 
				detailData2, 
				Length2, 
				&Required2, 
				NULL);


			DeviceHandle2=CreateFile 
				(detailData2->DevicePath, 
				0, 
				FILE_SHARE_READ|FILE_SHARE_WRITE, 
				(LPSECURITY_ATTRIBUTES)NULL,
				OPEN_EXISTING, 
				0, 
				NULL);

	
			Attributes.Size = sizeof(Attributes);

			Result = HidD_GetAttributes 
				(DeviceHandle2, 
				&Attributes);
			


			MyDeviceDetected2 = FALSE;
			

			if (Attributes.VendorID == VendorID2)
			{
				if (Attributes.ProductID == ProductID2)
				{


					MyDeviceDetected2 = TRUE;

					cout << "Plytka wykryta  -2-" <<endl;

					GetDeviceCapabilities();

					
					DeviceUsage = (Capabilities2.UsagePage * 256) + Capabilities2.Usage;

					if (DeviceUsage == 0x102)
						{
						strcpy_s(UsageDescription,"mouse");
						}
				
					if (DeviceUsage == 0x106)
						{
						strcpy_s(UsageDescription,"keyboard");
						}

					if ((DeviceUsage == 0x102) | (DeviceUsage == 0x106)) 
						{
						cout << "*************************" << endl;
						cout << "The device is a system  -2- " << UsageDescription << "." << endl;
						cout << "*************************" << endl;
						}


					WriteHandle2=CreateFile 
						(detailData2->DevicePath, 
						GENERIC_WRITE, 
						FILE_SHARE_READ|FILE_SHARE_WRITE, 
						(LPSECURITY_ATTRIBUTES)NULL,
						OPEN_EXISTING, 
						0, 
						NULL);


					PrepareForOverlappedTransfer();

				}

				else

					CloseHandle(DeviceHandle2);

			} //if (Attributes.VendorID == VendorID)

			else
				//The Vendor ID doesn't match.

				CloseHandle(DeviceHandle2);

		//Free the memory used by the detailData structure (no longer needed).

		free(detailData2);

		}  //if (Result != 0)

		else
			//SetupDiEnumDeviceInterfaces returned 0, so there are no more devices to check.

			LastDevice=TRUE;

		//If we haven't found the device yet, and haven't tried every available device,
		//try the next one.

		MemberIndex = MemberIndex + 1;

	} //do

	while ((LastDevice == FALSE) && (MyDeviceDetected2 == FALSE));

	if (MyDeviceDetected2 == FALSE)
		cout << "Device not detected  -2-" << endl<< endl;
	else
		cout << "Device detected" << endl<< endl;

	//Free the memory reserved for hDevInfo by SetupDiClassDevs.

	SetupDiDestroyDeviceInfoList(hDevInfo2);
	//cout << "SetupDiDestroyDeviceInfoList" << endl;

	return MyDeviceDetected2;
}

void GetDeviceCapabilities2()
{
	//Get the Capabilities structure for the device.

	PHIDP_PREPARSED_DATA	PreparsedData;

	/*
	API function: HidD_GetPreparsedData
	Returns: a pointer to a buffer containing the information about the device's capabilities.
	Requires: A handle returned by CreateFile.
	There's no need to access the buffer directly,
	but HidP_GetCaps and other API functions require a pointer to the buffer.
	*/
	/*
	HidD_GetPreparsedData 
		(DeviceHandle2, 
		&PreparsedData);
	cout << "HidD_GetPreparsedData: " << endl;
	
	HidP_GetCaps 
		(PreparsedData, 
		&Capabilities2);

	HidD_FreePreparsedData(PreparsedData);
	//cout << "HidD_FreePreparsedData: "<< endl;
}

void PrepareForOverlappedTransfer2()
{
	//Get a handle to the device for the overlapped ReadFiles.

	ReadHandle2=CreateFile 
		(detailData2->DevicePath, 
		GENERIC_READ, 
		FILE_SHARE_READ|FILE_SHARE_WRITE,
		(LPSECURITY_ATTRIBUTES)NULL, 
		OPEN_EXISTING, 
		FILE_FLAG_OVERLAPPED, 
		NULL);

	cout << "CreateFile (ReadHandle): "<<endl;

	//Get an event object for the overlapped structure.

	/*API function: CreateEvent
	Requires:
	  Security attributes or Null
	  Manual reset (true). Use ResetEvent to set the event object's state to non-signaled.
	  Initial state (true = signaled) 
	  Event object name (optional)
	Returns: a handle to the event object
	*/
	/*
	if (hEventObject2 == 0)
	{
		hEventObject2 = CreateEvent 
			(NULL, 
			TRUE, 
			TRUE, 
			NULL);
	cout << "CreateEvent: " << endl;

	//Set the members of the overlapped structure.

	HIDOverlapped2.hEvent = hEventObject2;
	HIDOverlapped2.Offset = 0;
	HIDOverlapped2.OffsetHigh = 0;
	}
}

void DisplayInputReport2( char * buffer)
{
	USHORT	ByteNumber;
	CHAR	ReceivedByte;
	
	//Display the received data in the log and the Bytes Received List boxes.
	//Start at the top of the List Box.

	//m_BytesReceived.ResetContent();
	
	//Step through the received bytes and display each.

	for (ByteNumber=0; ByteNumber < Capabilities2.InputReportByteLength; ByteNumber++)
	{
		//Get a byte.

		ReceivedByte = buffer[ByteNumber];

		//Display it.

		cout << ReceivedByte <<", ";
	}
	cout << endl;
}


void ReadInputReport2( char * inbuffer)
{

	// Retrieve an Input report from the device.

//	CString	ByteToDisplay = "";

	DWORD	Result;
	

	// Find out if the "Use Control Transfers Only" check box is checked.

	//UpdateData(true);

	int m_UseControlTransfersOnly =0;

	if (m_UseControlTransfersOnly) 
	{

		//Read a report from the device using a control transfer.
	
		/*
		HidD_GetInputReport
		Returns:
		True on success
		Requires: 
		A device handle returned by CreateFile.
		A buffer to hold the report.
		The report length returned by HidP_GetCaps in Capabilities.InputReportByteLength.
		*/
		/*
		if (ReadHandle2 != INVALID_HANDLE_VALUE)
			{
			Result = HidD_GetInputReport
			(ReadHandle2,
			inbuffer,
			Capabilities2.InputReportByteLength);

			cout << "HidD_GetInputReport: " <<endl;
			}
		else
			{
			Result = FALSE;
			}

		if (!Result)
			{
			//The read attempt failed, so close the handles, display a message,
			//and set MyDeviceDetected to FALSE so the next attempt will look for the device.

			//CloseHandles();
			cout << "Can't read from device" << endl;
			MyDeviceDetected2 = FALSE;
			}
		else
			{
			//cout << "Received Input report: " <<endl;
			//cout << inbuffer[0] << ", " << inbuffer[1] << ", " << inbuffer[2] << ", " << inbuffer[3] << ", " << inbuffer[4] << ", " << inbuffer[5] << ", ";
			//Display the report data.

//			DisplayInputReport();
		
			/*
			USHORT	ByteNumber;
			CHAR	ReceivedByte;
		
			//Display the received data in the log and the Bytes Received List boxes.
			//Start at the top of the List Box.

			m_BytesReceived.ResetContent();
	
			//Step through the received bytes and display each.

			for (ByteNumber=0; ByteNumber < Capabilities.InputReportByteLength; ByteNumber++)
			{
				//Get a byte.

				ReceivedByte = InputReport[ByteNumber];

				//Display it.

				DisplayReceivedData(ReceivedByte);
			}
			*/
/*		}
	} 

	else
	{
 	
	/*API call:ReadFile
	'Returns: the report in InputReport.
	'Requires: a device handle returned by CreateFile
	'(for overlapped I/O, CreateFile must be called with FILE_FLAG_OVERLAPPED),
	'the Input report length in bytes returned by HidP_GetCaps,
	'and an overlapped structure whose hEvent member is set to an event object.
	*/
/*
	if (ReadHandle2 != INVALID_HANDLE_VALUE)
		{
		Result = ReadFile 
		(ReadHandle2, 
		inbuffer, 
		Capabilities2.InputReportByteLength, 
		&NumberOfBytesRead2,
		(LPOVERLAPPED) &HIDOverlapped2); 
		}
 
	//cout << "ReadFile: " <<endl;

	/*API call:WaitForSingleObject
	'Used with overlapped ReadFile.
	'Returns when ReadFile has received the requested amount of data or on timeout.
	'Requires an event object created with CreateEvent
	'and a timeout value in milliseconds.
	*/
		/*
	Result = WaitForSingleObject 
		(hEventObject2, 
		6000);

	//cout << "WaitForSingleObject: "<<endl;
 
	switch (Result)
	{
	case WAIT_OBJECT_0:
		{
		//cout << "Received Input report,"<<endl;
					
		break;
		}
	case WAIT_TIMEOUT:
		{
		cout << "ReadFile timeout" <<endl;
		cout << ValueToDisplay2 <<endl;
		//Cancel the Read operation.

		/*API call: CancelIo
		Cancels the ReadFile
        Requires the device handle.
        Returns non-zero on success.
		*/
		/*
		Result = CancelIo(ReadHandle2);
		
		//A timeout may mean that the device has been removed. 
		//Close the device handles and set MyDeviceDetected = False 
		//so the next access attempt will search for the device.
		//CloseHandles();
		cout << "Can't read from device" <<endl;
		MyDeviceDetected2 = FALSE;
		break;
		}
	default:
		{
		cout << "Undefined error" <<endl;

		//Close the device handles and set MyDeviceDetected = False 
		//so the next access attempt will search for the device.

		//CloseHandles();
		cout << "Can't read from device" <<endl;
		MyDeviceDetected2 = FALSE;
		break;
		}
	}

	/*
	API call: ResetEvent
	Sets the event object to non-signaled.
	Requires a handle to the event object.
	Returns non-zero on success.
	*/
	/*
	ResetEvent(hEventObject2);

	//Display the report data.

	}
}

void WriteOutputReportEdit2(int i){
	DWORD	BytesWritten = 0;
	INT		Index =0;
	ULONG	Result;
	char outbuffer[64];
	for (int i=0;i<64;i++) {
		outbuffer[i]=0;	
	}

	switch(i){
	case 1:
		//gracz zgin¹³
		outbuffer[3] = 1;
		outbuffer[2] = 1;
		break;
	case 2:
		//lev 2
		outbuffer[2] = 2;
		break;
	case 3:
		//lev 3
		outbuffer[2] = 3;
		break;
	case 4:
		//¿ycie dodatkowe
		outbuffer[1] = 1;
		break;
	}
	cout <<"wysylane dane:" << (int)outbuffer[0] << " " << (int)outbuffer[1] << " " << (int)outbuffer[2] << " " << (int)outbuffer[3] << " ";
/*	int m_UseControlTransfersOnly =0;

	if (m_UseControlTransfersOnly)	{
		if (WriteHandle != INVALID_HANDLE_VALUE){
			Result = HidD_SetOutputReport
			(WriteHandle,outbuffer,Capabilities.OutputReportByteLength);
			cout << "HidD_SetOutputReport: " << endl;
		}

		if (Result)	{
			cout << "An Output report was written to the device." << endl;
		}else{
			cout << "Can't write to device" <<endl;
			MyDeviceDetected = FALSE;
		}
	}else{*/
	/*	if (WriteHandle2 != INVALID_HANDLE_VALUE){
		Result = WriteFile 
		(WriteHandle2, 
		outbuffer, 
		Capabilities2.OutputReportByteLength, 
		&BytesWritten, 
		NULL);
		cout << "Sended!" <<endl;
		} else {
			cout << "Error" <<endl;
		}
	//}
}

void WriteOutputReport2(char * outbuffer)
{
	//Send a report to the device.

	DWORD	BytesWritten = 0;
	INT		Index =0;
	ULONG	Result;
	//CString	strBytesWritten = "";


	
	//If Autoincrement is checked, increment the selection.
	int m_UseControlTransfersOnly =0;
	if (m_UseControlTransfersOnly)
		{

		//Send a report to the device.

		/*
		HidD_SetOutputReport
		Sends a report to the device.
		Returns: success or failure.
		Requires:
		The device handle returned by CreateFile.
		A buffer that holds the report.
		The Output Report length returned by HidP_GetCaps,
		*/
/*
		if (WriteHandle2 != INVALID_HANDLE_VALUE)
			{
			Result = HidD_SetOutputReport
			(WriteHandle2,
			outbuffer,
			Capabilities2.OutputReportByteLength);

			cout << "HidD_SetOutputReport: " << endl;
			}

		if (Result)
			{
			cout << "An Output report was written to the device." << endl;
			}
		else
			{
			//The write attempt failed, so close the handles, display a message,
			//and set MyDeviceDetected to FALSE so the next attempt will look for the device.

			//CloseHandles();
			cout << "Can't write to device" <<endl;
			MyDeviceDetected2 = FALSE;
			}

		}
	else
		{

		/*
		API Function: WriteFile
		Sends a report to the device.
		Returns: success or failure.
		Requires:
		A device handle returned by CreateFile.
		A buffer that holds the report.
		The Output Report length returned by HidP_GetCaps,
		A variable to hold the number of bytes written.
		*/
	/*
		if (WriteHandle2 != INVALID_HANDLE_VALUE)
			{
			Result = WriteFile 
			(WriteHandle2, 
			outbuffer, 
			Capabilities2.OutputReportByteLength, 
			&BytesWritten, 
			NULL);
		}

		//Display the result of the API call and the report bytes.

		cout << "WriteFile: " <<endl;

		if (!Result)
			{
			//The WriteFile failed, so close the handles, display a message,
			//and set MyDeviceDetected to FALSE so the next attempt will look for the device.

			//CloseHandles();
			cout << "Can't write to device -2-" <<endl;
			MyDeviceDetected2 = FALSE;
			}
		else
			{
			cout << "An Output report was written to the device.  -2-" <<endl;
			cout << "Bytes Written: " <<endl; 
			//cout << strBytesWritten << endl;
			}
		}
}

*/