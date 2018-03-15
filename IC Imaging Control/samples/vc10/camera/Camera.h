

#include "ICImagingControl\include\tisudshl.h" 

bool OpenCamera();
bool StartCamera();
void SuspendCamera();
void CloseCamera();

bool GetImageBuffer(DShowLib::Grabber::tMemBufferPtr* bufferR, DShowLib::Grabber::tMemBufferPtr* bufferL);

