#include "_STM.h"
#include "main.h"

#pragma comment(lib,"setupapi.lib")
#pragma comment(lib,"hid.lib")

	DWORD								ActualBytesRead;
	DWORD								BytesRead;
	HIDP_CAPS							Capabilities;
	DWORD								cbBytesRead;
	PSP_DEVICE_INTERFACE_DETAIL_DATA	detailData;
	HANDLE								DeviceHandle;
	DWORD								dwError;
	char								FeatureReport[256];
	HANDLE								hEventObject;
	HANDLE								hDevInfo;
	GUID								HidGuid;
	OVERLAPPED							HIDOverlapped;
	char								InputReport[256];
	ULONG								Length;
	LPOVERLAPPED						lpOverLap;
	bool								MyDeviceDetected = FALSE; 
	char								MyDevicePathName[50];
	DWORD								NumberOfBytesRead;
	char								OutputReport[256];
	HANDLE								ReadHandle;
	DWORD								ReportType;
	ULONG								Required;
	char								ValueToDisplay[50];
	HANDLE								WriteHandle;

	int VendorID = 0x0477;
	int ProductID = 0x5620;

bool FindTheHID()
{

	HIDD_ATTRIBUTES						Attributes;
	DWORD								DeviceUsage;
	SP_DEVICE_INTERFACE_DATA			devInfoData;
	bool								LastDevice = FALSE;
	int									MemberIndex = 0;
	LONG								Result;	
	char								UsageDescription[50];

	Length = 0;
	detailData = NULL;
	DeviceHandle=NULL;

	HidD_GetHidGuid(&HidGuid);	
	
	hDevInfo=SetupDiGetClassDevs 
		(&HidGuid, 
		NULL, 
		NULL, 
		DIGCF_PRESENT|DIGCF_INTERFACEDEVICE);
		
	devInfoData.cbSize = sizeof(devInfoData);


	MemberIndex = 0;
	LastDevice = FALSE;

	do
	{

		Result=SetupDiEnumDeviceInterfaces 
			(hDevInfo, 
			0, 
			&HidGuid, 
			MemberIndex, 
			&devInfoData);

		if (Result != 0)
		{

			Result = SetupDiGetDeviceInterfaceDetail 
				(hDevInfo, 
				&devInfoData, 
				NULL, 
				0, 
				&Length, 
				NULL);

			detailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(Length);
			

			detailData -> cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);


			Result = SetupDiGetDeviceInterfaceDetail 
				(hDevInfo, 
				&devInfoData, 
				detailData, 
				Length, 
				&Required, 
				NULL);


			DeviceHandle=CreateFile 
				(detailData->DevicePath, 
				0, 
				FILE_SHARE_READ|FILE_SHARE_WRITE, 
				(LPSECURITY_ATTRIBUTES)NULL,
				OPEN_EXISTING, 
				0, 
				NULL);

	
			Attributes.Size = sizeof(Attributes);

			Result = HidD_GetAttributes 
				(DeviceHandle, 
				&Attributes);
			


			MyDeviceDetected = FALSE;
			

			if (Attributes.VendorID == VendorID)
			{
				if (Attributes.ProductID == ProductID)
				{


					MyDeviceDetected = TRUE;

					cout << "Plytka wykryta" <<endl;

					GetDeviceCapabilities();

					
					DeviceUsage = (Capabilities.UsagePage * 256) + Capabilities.Usage;

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
						cout << "The device is a system " << UsageDescription << "." << endl;
						cout << "*************************" << endl;
						}


					WriteHandle=CreateFile 
						(detailData->DevicePath, 
						GENERIC_WRITE, 
						FILE_SHARE_READ|FILE_SHARE_WRITE, 
						(LPSECURITY_ATTRIBUTES)NULL,
						OPEN_EXISTING, 
						0, 
						NULL);


					PrepareForOverlappedTransfer();

				}

				else

					CloseHandle(DeviceHandle);

			} //if (Attributes.VendorID == VendorID)

			else
				//The Vendor ID doesn't match.

				CloseHandle(DeviceHandle);

		//Free the memory used by the detailData structure (no longer needed).

		free(detailData);

		}  //if (Result != 0)

		else
			//SetupDiEnumDeviceInterfaces returned 0, so there are no more devices to check.

			LastDevice=TRUE;

		//If we haven't found the device yet, and haven't tried every available device,
		//try the next one.

		MemberIndex = MemberIndex + 1;

	} //do

	while ((LastDevice == FALSE) && (MyDeviceDetected == FALSE));

	if (MyDeviceDetected == FALSE)
		cout << "Device not detected" << endl<< endl;
	else
		cout << "Device detected" << endl<< endl;

	//Free the memory reserved for hDevInfo by SetupDiClassDevs.

	SetupDiDestroyDeviceInfoList(hDevInfo);
	//cout << "SetupDiDestroyDeviceInfoList" << endl;

	return MyDeviceDetected;
}

void GetDeviceCapabilities()
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

	HidD_GetPreparsedData 
		(DeviceHandle, 
		&PreparsedData);
	cout << "HidD_GetPreparsedData: " << endl;
	
	HidP_GetCaps 
		(PreparsedData, 
		&Capabilities);

	HidD_FreePreparsedData(PreparsedData);
	//cout << "HidD_FreePreparsedData: "<< endl;
}

void PrepareForOverlappedTransfer()
{
	//Get a handle to the device for the overlapped ReadFiles.

	ReadHandle=CreateFile 
		(detailData->DevicePath, 
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

	if (hEventObject == 0)
	{
		hEventObject = CreateEvent 
			(NULL, 
			TRUE, 
			TRUE, 
			NULL);
	cout << "CreateEvent: " << endl;

	//Set the members of the overlapped structure.

	HIDOverlapped.hEvent = hEventObject;
	HIDOverlapped.Offset = 0;
	HIDOverlapped.OffsetHigh = 0;
	}
}

void DisplayInputReport( char * buffer)
{
	USHORT	ByteNumber;
	CHAR	ReceivedByte;
	
	//Display the received data in the log and the Bytes Received List boxes.
	//Start at the top of the List Box.

	//m_BytesReceived.ResetContent();
	
	//Step through the received bytes and display each.

	for (ByteNumber=0; ByteNumber < Capabilities.InputReportByteLength; ByteNumber++)
	{
		//Get a byte.

		ReceivedByte = buffer[ByteNumber];

		//Display it.

		cout << ReceivedByte <<", ";
	}
	cout << endl;
}


void ReadInputReport( char * inbuffer)
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
		
		if (ReadHandle != INVALID_HANDLE_VALUE)
			{
			Result = HidD_GetInputReport
			(ReadHandle,
			inbuffer,
			Capabilities.InputReportByteLength);

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
			MyDeviceDetected = FALSE;
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
		}
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

	if (ReadHandle != INVALID_HANDLE_VALUE)
		{
		Result = ReadFile 
		(ReadHandle, 
		inbuffer, 
		Capabilities.InputReportByteLength, 
		&NumberOfBytesRead,
		(LPOVERLAPPED) &HIDOverlapped); 
		}
 
	//cout << "ReadFile: " <<endl;

	/*API call:WaitForSingleObject
	'Used with overlapped ReadFile.
	'Returns when ReadFile has received the requested amount of data or on timeout.
	'Requires an event object created with CreateEvent
	'and a timeout value in milliseconds.
	*/

	Result = WaitForSingleObject 
		(hEventObject, 
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
		cout << ValueToDisplay <<endl;
		//Cancel the Read operation.

		/*API call: CancelIo
		Cancels the ReadFile
        Requires the device handle.
        Returns non-zero on success.
		*/
		
		Result = CancelIo(ReadHandle);
		
		//A timeout may mean that the device has been removed. 
		//Close the device handles and set MyDeviceDetected = False 
		//so the next access attempt will search for the device.
		//CloseHandles();
		cout << "Can't read from device" <<endl;
		MyDeviceDetected = FALSE;
		break;
		}
	default:
		{
		cout << "Undefined error" <<endl;

		//Close the device handles and set MyDeviceDetected = False 
		//so the next access attempt will search for the device.

		//CloseHandles();
		cout << "Can't read from device" <<endl;
		MyDeviceDetected = FALSE;
		break;
		}
	}

	/*
	API call: ResetEvent
	Sets the event object to non-signaled.
	Requires a handle to the event object.
	Returns non-zero on success.
	*/

	ResetEvent(hEventObject);

	//Display the report data.

	}
}

void WriteOutputReportEdit(int i){
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
		if (WriteHandle != INVALID_HANDLE_VALUE){
		Result = WriteFile 
		(WriteHandle, 
		outbuffer, 
		Capabilities.OutputReportByteLength, 
		&BytesWritten, 
		NULL);
		cout << "Sended!" <<endl;
		} else {
			cout << "Error" <<endl;
		}
	//}
}

void WriteOutputReport(char * outbuffer)
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

		if (WriteHandle != INVALID_HANDLE_VALUE)
			{
			Result = HidD_SetOutputReport
			(WriteHandle,
			outbuffer,
			Capabilities.OutputReportByteLength);

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
			MyDeviceDetected = FALSE;
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

		if (WriteHandle != INVALID_HANDLE_VALUE)
			{
			Result = WriteFile 
			(WriteHandle, 
			outbuffer, 
			Capabilities.OutputReportByteLength, 
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
			cout << "Can't write to device" <<endl;
			MyDeviceDetected = FALSE;
			}
		else
			{
			cout << "An Output report was written to the device." <<endl;
			cout << "Bytes Written: " <<endl; 
			//cout << strBytesWritten << endl;
			}
		}
}
