// #include "Scene.h"



// enum input_code {
//     imsize,
//     eye,
//     viewdir,
//     hfov,
//     updir,
//     bkgcolor,
//     mtlcolor,
//     texture,
//     sphere,
//     v,
//     vn,
//     vt,
//     f,
//     light,
//     comment
// };

// int hashInputCode(std::string code) {
//     if (code == "texture") return texture;
//     if (code == "eye") return eye;
//     if (code == "viewdir") return viewdir;
//     if (code == "hfov") return hfov;
//     if (code == "updir") return updir;
//     if (code == "bkgcolor") return bkgcolor;
//     if (code == "mtlcolor") return mtlcolor;
//     if (code == "texture") return texture;
//     if (code == "sphere") return sphere;
//     if (code == "v") return v;

    
    
//     // ,
//     // ,
//     // ,
//     // v,
//     // vn,
//     // vt,
//     // f,
//     // light,
//     // comment

//     return 0;
// }

// std::ostream& operator << (std::ostream& os, const Scene& material){


//     return os;
// }
// std::istream& operator >> (std::istream& is, Scene& material) {

//     std::string word;

//     while(is >> word) {
//         printf("loading %s\n", word.c_str());

//         int code = hashInputCode(word);

//         switch(code) {
//             case imsize:

//                 // Load image size

//                 break;
//             case eye:
//                 break;
//             case viewdir:
//                 break;
//             case hfov:
//                 break;
//             case updir:
//                 break;
//             case bkgcolor:
//                 break;
//             case mtlcolor:
//                 break;
//             case texture:
//                 break;
//             case sphere:
//                 break;
//             case v:
//                 break;
//             case vn:
//                 break;
//             case vt:
//                 break;
//             case f:
//                 break;
//             case light:
//                 break;
//             case comment:
//                 break;

//             default:
//         }
//     }
    

//     return is;
// }
