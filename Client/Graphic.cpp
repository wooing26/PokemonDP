#include "pch.h"
#include "Graphic.h"

Graphic::Graphic()
{
}

Graphic::~Graphic()
{
	Clear();
	SAFE_RELEASE(_directFactory);
}

HRESULT Graphic::Init(HWND hwnd)
{
	HRESULT hr = S_OK;

	hr = ::D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_directFactory);

	if (hr == S_OK)
	{
		RECT rect;
		::GetClientRect(hwnd, &rect);
		D2D1_SIZE_U size = D2D1::SizeU(rect.right - rect.left, rect.bottom - rect.top);

		hr = _directFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hwnd, size),
			&_renderTarget);
	}

    if (hr == S_OK)
    {
        hr = _renderTarget->CreateSolidColorBrush(
            D2D1::ColorF(D2D1::ColorF::LightSlateGray), &myLightSlateGrayBrush
        );
    }
    if (hr == S_OK)
    {
        hr = _renderTarget->CreateSolidColorBrush(
            D2D1::ColorF(D2D1::ColorF::CornflowerBlue), &myCornflowerBlueBrush
        );
    }
    

	return hr;
}

void Graphic::Render()
{
    HRESULT hr = S_OK;
    
    
    if (SUCCEEDED(hr)) {
        _renderTarget->BeginDraw();
        _renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
        _renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

        D2D1_SIZE_F rtSize = _renderTarget->GetSize();

        int width = static_cast<int>(rtSize.width);
        int height = static_cast<int>(rtSize.height);
        for (int x = 0; x < width; x += 10) {
            _renderTarget->DrawLine(D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
                D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
                myLightSlateGrayBrush, 0.5f);
        }
        for (int y = 0; y < height; y += 10) {
            _renderTarget->DrawLine(D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
                D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
                myLightSlateGrayBrush, 0.5f);
        }

        D2D1_RECT_F rectangle1 = D2D1::RectF(
            rtSize.width / 2 - 50.0f, rtSize.height / 2 - 50.0f,
            rtSize.width / 2 + 50.0f, rtSize.height / 2 + 50.0f
        );
        D2D1_RECT_F rectangle2 = D2D1::RectF(
            rtSize.width / 2 - 100.0f, rtSize.height / 2 - 100.0f,
            rtSize.width / 2 + 100.0f, rtSize.height / 2 + 100.0f
        );
        _renderTarget->FillRectangle(&rectangle1, myLightSlateGrayBrush);
        _renderTarget->DrawRectangle(&rectangle2, myCornflowerBlueBrush);

        hr = _renderTarget->EndDraw();
    }

    if (hr == D2DERR_RECREATE_TARGET) {
        hr = S_OK;
        Clear();
    }
}

void Graphic::Clear()
{
	SAFE_RELEASE(_renderTarget);
}

void Graphic::Resize(uint32 width, uint32 height)
{
	if (_renderTarget == nullptr)
		return;

	_renderTarget->Resize(D2D1::SizeU(width, height));
}
