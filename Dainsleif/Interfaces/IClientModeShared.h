#pragma once
#include "../Vector.h"

class IClientModeShared
{
public:

};

struct ViewSetup
{
    int m_iX;
    int m_iUnscaledX;
    int m_iY;
    int m_iUnscaledY;
    int m_iWidth;
    int m_iUnscaledWidth;
    int m_iHeight;
    int m_iUnscaledHeight;
    bool m_bOrtho;
    float m_flOrthoLeft;
    float m_flOrthoTop;
    float m_flOrthoRight;
    float m_flOrthoBottom;
    std::byte m_pad0[0x7C];
    float m_flFOV;
    float m_flViewModelFOV;
    Vector3 m_vecOrigin;
    Vector3 m_angView;
    float m_flNearZ;
    float m_flFarZ;
    float m_flNearViewmodelZ;
    float m_flFarViewmodelZ;
    float m_flAspectRatio;
    float m_flNearBlurDepth;
    float m_flNearFocusDepth;
    float m_flFarFocusDepth;
    float m_flFarBlurDepth;
    float m_flNearBlurRadius;
    float m_flFarBlurRadius;
    float m_flDoFQuality;
    int m_nMotionBlurMode;
    float m_flShutterTime;
    Vector3 m_vecShutterOpenPosition;
    Vector3 m_vecShutterOpenAngles;
    Vector3 m_vecShutterClosePosition;
    Vector3 m_vecShutterCloseAngles;
    float m_flOffCenterTop;
    float m_flOffCenterBottom;
    float m_flOffCenterLeft;
    float m_flOffCenterRight;
    bool m_bOffCenter : 1;
    bool m_bRenderToSubrectOfLargerScreen : 1;
    bool m_bDoBloomAndToneMapping : 1;
    bool m_bDoDepthOfField : 1;
    bool m_bHDRTarget : 1;
    bool m_bDrawWorldNormal : 1;
    bool m_bCullFontFaces : 1;
    bool m_bCacheFullSceneState : 1;
    bool m_bCSMView : 1;
};
