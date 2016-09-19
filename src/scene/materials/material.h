#pragma once
#include <la.h>
#include <bmp/EasyBMP.h>
#include <scene/materials/bxdfs/bxdf.h>
#include <raytracing/intersection.h>
#include <QImage>
#include <random>
#include <raytracing/samplers/stratifiedpixelsampler.h>

class Geometry;
class Intersection;

class Material
{
public:
//Constructors/Destructors
    Material();
    Material(const glm::vec3 &color);
    virtual ~Material(){}

//Functions
    //Given an intersection with some Geometry, evaluate the scattered energy at isx given a world-space wo and wi for all BxDFs we contain that match the input flags
    virtual glm::vec3 EvaluateScatteredEnergy(const Intersection &isx, const glm::vec3 &woW, const glm::vec3 &wiW, float& pdf, BxDFType flags = BSDF_ALL) ;

    //Given an intersection with some Geometry, generate a world-space wi then evaluate the scattered energy along the world-space wo.
    virtual glm::vec3 SampleAndEvaluateScatteredEnergy(const Intersection &isx, const glm::vec3 &woW, glm::vec3 &wiW_ret, float &pdf_ret, BxDFType flags = BSDF_ALL) ;

    //Given an intersection with some Geometry and a number of samples to take, generate a set of N random vec2s.
    //Then, pass this information to each BxDF that matches the input flags and return their combined EHSE results
    virtual glm::vec3 EvaluateHemisphereScatteredEnergy(const Intersection &isx, const glm::vec3 &wo, int num_samples, BxDFType flags = BSDF_ALL) ;

    //A shorthand way of calling EvaluateHemisphereScatteredEnergy
    glm::vec3 Rho(const Intersection &isx, const glm::vec3 &wo, int num_samples, BxDFType flags = BSDF_ALL)  {return EvaluateHemisphereScatteredEnergy(isx, wo, num_samples, flags);}

    //Returns the RGB color stored in the input image as a vec3 with values ranging from 0 to 1.
    //Note that this is a STATIC function, so you don't need to call it from an instance of Material
    static glm::vec3 GetImageColor(const glm::vec2 &uv_coord, const QImage * const &image);
    static glm::vec3 GetImageColorInterp(const glm::vec2 &uv_coord, const QImage * const &image);

    //std::mt19937 generator;
    //std::uniform_real_distribution<float> uniform_distribution;

    // PHOTON_MAPPING
    //sample bxdf , return pdf, flags, fr and wi
    virtual glm::vec3 BSDF_Sample_f(glm::vec3 &woW, float u[], glm::vec3 &wiW, float &pdf, BxDFType &sampledType, BxDFType flags = BSDF_ALL);

    // rho
    virtual glm::vec3 rho(BxDFType flags, std::uniform_real_distribution<float>& rndDistr, std::mt19937 &rndGenerator, int numSamples = 6);

    virtual glm::vec3 rho(const glm::vec3 &wo, std::uniform_real_distribution<float> &rndDistr, std::__1::mt19937 &rndGenerator, BxDFType flags = BSDF_ALL, int sqrtSamples = 6);

    // number components
    int NumComponents(BxDFType flags);

//Member Variables
    QString name;           //The name given in the scene XML file
    QList<BxDF*> bxdfs;     //The set of BxDFs to which this Material can refer when computing the color at a given intersection.
    bool is_light_source;   //A quick way to check if this material is that of a light source. If TRUE, the owning geometry is treated as an area light.
                            //Its color is base_color * texture, and its intensity is set by the intensity member variable

    glm::vec3 base_color;   //Multiplied by texture color
    float intensity;        //Only used for light sources

    QImage* texture;   //When non-null, the Material has a texture assigned to it.
                    //A Material's texture is multiplied with its base_color to determine its color at a given point in space.
    QImage* normal_map;
};