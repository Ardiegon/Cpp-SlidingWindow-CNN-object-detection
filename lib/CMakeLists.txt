add_library(
    point
    point/point.hpp
    point/point.cpp
)

add_library(
    obdet
    obdet/obdet.hpp
    obdet/SampleTemplate.cpp
    obdet/Sample.cpp
    obdet/ImgSamples.cpp
    obdet/TemplateMatch.cpp
)

add_library(
    optmg
    optmg/optmg.hpp
    optmg/OptionManager.cpp
)
