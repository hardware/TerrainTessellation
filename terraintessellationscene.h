#ifndef TERRAINTESSELLATIONSCENE_H
#define TERRAINTESSELLATIONSCENE_H

#include "abstractscene.h"
#include "material.h"

#include <QOpenGLBuffer>
#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include <QStringList>

class Camera;

class QOpenGLFunctions_4_0_Core;

class TerrainTessellationScene : public AbstractScene
{
    Q_OBJECT

public:
    TerrainTessellationScene( QObject* parent = 0 );

    virtual void initialise();
    virtual void update( float t );
    virtual void render();
    virtual void resize( int w, int h );

    // Camera motion control
    void setSideSpeed( float vx ) { m_v.setX( vx ); }
    void setVerticalSpeed( float vy ) { m_v.setY( vy ); }
    void setForwardSpeed( float vz ) { m_v.setZ( vz ); }
    void setViewCenterFixed( bool b ) { m_viewCenterFixed = b; }

    // Camera orientation control
    void pan( float angle ) { m_panAngle = angle; }
    void tilt( float angle ) { m_tiltAngle = angle; }

    // Terrain scales
    void setTerrainHorizontalScale( float horizontalScale ) { m_horizontalScale = horizontalScale; }
    float terrainHorizontalScale() const { return m_horizontalScale; }
    void setTerrainVerticalScale( float verticalScale ) { m_verticalScale = verticalScale; }
    float terrainVerticalScale() const { return m_verticalScale; }

    // Sun position
    void setSunAngle( float sunAngle ) { m_sunTheta = sunAngle; qDebug() << m_sunTheta; }
    float sunAngle() const { return m_sunTheta; }

    // Screen space error - tessellation control
    void setScreenSpaceError( float error ) { m_screenSpaceError = error; qDebug() << error; }
    float screenSpaceError() const { return m_screenSpaceError; }

    enum DisplayMode {
        SimpleWireFrame = 0,
        WorldHeight,
        WorldNormals,
        Grass,
        GrassAndRocks,
        GrassRocksAndSnow,
        LightingFactors,
        TexturedAndLit,
        DisplayModeCount
    };

    void setDisplayMode( DisplayMode displayMode ) { m_displayMode = displayMode; }
    DisplayMode displayMode() const { return m_displayMode; }

private:
    void prepareShaders();
    void prepareTextures();
    void prepareVertexBuffers( QSize heightMapSize );
    void prepareVertexArrayObject();

    Camera* m_camera;
    QVector3D m_v;
    bool m_viewCenterFixed;
    float m_panAngle;
    float m_tiltAngle;

    QMatrix4x4 m_viewportMatrix;
    QVector2D m_viewportSize;

    // The terrain "object"
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_patchBuffer;
    int m_patchCount;
    float m_screenSpaceError;
    MaterialPtr m_material;

    // Terrain rendering controls
    QMatrix4x4 m_modelMatrix;
    float m_horizontalScale;
    float m_verticalScale;

    // Angle of sun. 0 is directly overhead, 90 to the East, -90 to the West
    float m_sunTheta;

    float m_time;
    const float m_metersToUnits;

    DisplayMode m_displayMode;
    QStringList m_displayModeNames;
    QVector<GLuint> m_displayModeSubroutines;

    QOpenGLFunctions_4_0_Core* m_funcs;
    QSize m_heightMapSize;
};

#endif // TERRAINTESSELLATIONSCENE_H
