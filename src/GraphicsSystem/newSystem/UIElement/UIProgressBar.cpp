#include "UIProgressBar.h"

UIProgressBar::UIProgressBar(
    std::shared_ptr<RenderingSystem> &aRenderingContext,
    const Texture2D &background,
    const Texture2D &foreground,
    bool aIsVertical)
    : Leaf(aRenderingContext)
    , backTexture(background)
    , frontTexture(foreground)
    , isVertical(aIsVertical)
{
}

void UIProgressBar::calculateProgress(int current, int max)
{
    if (max <= 0)
    {
        return;
    }

    if (current >= max)
    {
        if (backSize.IsZero())
        {
            return;
        }

        current = max;
    }

    double coeff = (current + 0.0) / max; // коэффициент для получения частей изображений.

    Size progressSize = backTexture.getSize(); // размеры текстур (back и front) должны быть одинаковыми.
    Position progressPosition = getPosition();
    Size originalTextureSize = backTexture.getOriginalTextureSize(); // физические размеры текстур тоже одинаковые.

    if (isVertical)
    {
        frontSize.width = progressSize.width;

        if (current < max)
        {
            backSize.width = progressSize.width;
            backSize.height = getMeasurementPart(progressSize.height, 1 - coeff);

            frontSize.height = progressSize.height - backSize.height;

            int backRectHeight = getMeasurementPart(originalTextureSize.height, 1 - coeff);
            backRect = SDL_Rect
                {
                    0,
                    0,
                    originalTextureSize.width,
                    backRectHeight
                };

            frontRect = SDL_Rect
                {
                    0,
                    backRectHeight,
                    originalTextureSize.width,
                    originalTextureSize.height - backRectHeight
                };

            backDrawPosition = progressPosition;
            frontDrawPosition = Position{backDrawPosition.x, backDrawPosition.y + backSize.height};
        }
        else
        {
            backSize.width = 0; // Не нужно отрисовывать подложку, если шкала заполнена.
            backSize.height = 0;

            frontSize.height = progressSize.height;
        }
    }
    else
    {

        frontSize.height = progressSize.height;

        if (current < max)
        {
            backSize.height = progressSize.height;
            backSize.width = getMeasurementPart(progressSize.width, 1 - coeff);

            frontSize.width = progressSize.width - backSize.width;

            int frontRectWidth = getMeasurementPart(originalTextureSize.width, coeff);


            frontRect = SDL_Rect
                {
                    0,
                    0,
                    frontRectWidth,
                    originalTextureSize.height
                };

            backRect = SDL_Rect
                {
                    frontRectWidth,
                    0,
                    originalTextureSize.width - frontRectWidth,
                    originalTextureSize.height
                };

            frontDrawPosition = progressPosition;// т.к. значение уменьшается справа налево
            backDrawPosition = Position{frontDrawPosition.x + frontSize.width, frontDrawPosition.y};
        }
        else
        {
            backSize.width = 0; // Не нужно отрисовывать подложку, если шкала заполнена.
            backSize.height = 0;

            frontSize.width = progressSize.width;
        }
    }
}

void UIProgressBar::draw() const
{
    if (backSize.IsZero())
    {
        frontTexture.drawAtPosition(getPosition());
    }
    else
    {
        backTexture.drawScaledPartAtPosition(backDrawPosition, backSize, &backRect);
        frontTexture.drawScaledPartAtPosition(frontDrawPosition, frontSize, &frontRect);
    }
}

Size UIProgressBar::getSize() const
{
    return backTexture.getSize();
}

void UIProgressBar::setSize(Size size)
{
    backTexture.setSize(size);
    frontTexture.setSize(size);

    backSize = Size{0, 0};
    frontSize = size;
}

int UIProgressBar::getMeasurementPart(int aValue, double aCoeff) const
{
    return static_cast<int>(aValue * aCoeff);
}

void UIProgressBar::ConnectMethod(std::function<void (std::string)> method)
{
    connectedMethod = method;
}

bool UIProgressBar::onClick(Position point)
{
    SDL_Rect rect = SDL_Rect();
    rect.x = getPosition().x;
    rect.y = getPosition().y;
    rect.w = getSize().width;
    rect.h = getSize().height;

    SDL_Point sPoint{point.x, point.y};

    bool result = SDL_PointInRect(&sPoint, &rect);

    if (result)
        connectedMethod("zero");

    return result;
}
