#include "Scene.h"


/**
 * @brief 
 * 
 * @param n_i 
 * @param n_t 
 * @param N 
 * @param I 
 * @return float 
 */

float calculateFresnel(float n_i, float n_t, Vector3 N, Vector3 I) {

    N.normalize();
    I.normalize();


    float Fr;
    float F0 = pow((n_t - n_i) / (n_t + n_i), 2);

    float cosine = N.dotProduct(I);

    //cosine *= -1;

    // if the current is more dense then there is a chance of internal refraction
    
    if(n_i > n_t) {
        float ratio = n_i/n_t;
        float sine = (1.0 - cosine * cosine);

        if(sqrt(sine) > 1.0)
            return -1.0;
        cosine = sqrt(1.0 - sine * sine);
    }
    

    Fr = F0 + (1.0f - F0) * pow((1.0f - cosine), 5);
    //if( Fr > 1.0f) 
        //std::cout << "fresnel: " << Fr << '\n';
    return Fr;
}

/**
 * @brief Construct a new Scene:: Scene object
 * 
 */

Scene::Scene() {
    mainCamera = nullptr;
}
/**
 * @brief Destroy the Scene:: Scene object
 * 
 */

Scene::~Scene() {
    if(mainCamera != nullptr)
        delete mainCamera;
}

/**
 * @brief 
 * 
 * @param cam 
 */

void Scene::setMainCamera(Camera *cam) {
    mainCamera = cam;
}

void Scene::addObject(VisibleObject *obj) {
    visibleObjects.push_back(obj);
}

void Scene::addLight(Light *l) {
    lightObjects.push_back(l);
}

/**
 * @brief this function loads a scene from a pre-formatted text file.
 * 
 * @param fileName 
 */

void Scene::LoadFromFile(std::string fileName) {

    Material *current_material; // Reference to material for the current object being read

    std::vector<Vector3 *> verticies;
    std::vector<Vector3 *> vertNormals;
    std::vector<Face *> faces;

    std::vector<std::array <int, 2> > text_maps;

    if(this->mainCamera == nullptr) {
        this->setMainCamera(new Camera());
    }

    this->name = fileName.substr(0, fileName.length() - 4);
    // open up file
    std::ifstream inputFile;

    inputFile.open(fileName);

    std::string line;

    if(!inputFile.is_open()) {
        perror("Input file count not be opened.\n");
        exit(1);
    }

    std::string word; // reads every word of the file
    // read file
    while(inputFile >> word) {

        printf("loading %s\n", word.c_str());

        if(word == "imsize") {
            float w, h;
            inputFile >> w >> h;

            this->mainCamera->setResolution(w,h);
        }
        else if(word == "eye") {
            Vector3 eye_pos;
            inputFile >> eye_pos;

            this->getMainCamera()->setPosition(eye_pos);
        }
        else if(word == "viewdir") {
            Vector3 view_dir;
            inputFile >> view_dir;

            this->getMainCamera()->setViewDir(view_dir);
        }
        else if(word == "hfov") {
            float h_fov;

            inputFile >> h_fov;
            this->getMainCamera()->setFOV(h_fov);
        }
        else if(word == "updir") {
            Vector3 up_dir;
            inputFile >> up_dir;

            this->getMainCamera()->setUpDirection(up_dir);
        }
        else if(word == "bkgcolor") {

            Material bkg_material;

            inputFile >> bkg_material;

            //PPMColor bkg_color;
            //inputFile >> bkg_color;

            this->setBackgroundMaterial(bkg_material);
        }
        else if(word == "mtlcolor") {

            Material *m = new Material();     
            inputFile >> *m;
            current_material = m;
            std::cout << "Updated new material!\n";
        }
        else if(word == "texture") {
            std::string texture_file_name;

            inputFile >> texture_file_name;
            PPMImage *texture = new PPMImage();
            texture->readFromFile(texture_file_name);         
            current_material->setTexture(texture);

            std::cout << "Updated new texture!\n";
        }
        else if(word == "sphere") {  

            

            Vector3 ball_pos;
            float r;
            inputFile >> ball_pos >> r;
            
            Sphere *ball = new Sphere(ball_pos, r);
            ball->setMaterial(current_material);
            this->addObject(ball);
            std::cout <<"Created sphere!\n";
            //shapes.push_back(ball);
        }
        else if(word == "v") {
            // verticy detected

            Vector3 *v = new Vector3();
            inputFile >> *v;
            verticies.push_back(v);
        }
        else if(word == "vn") {
            // verticy normal detected
            Vector3 *vn = new Vector3();
            inputFile >> *vn;
            vertNormals.push_back(vn);
        }
        else if(word == "vt") {
            std::array<int, 2> text;
            inputFile >> text[0] >> text[1];
            text_maps.push_back(text);
            std::cout << "First element: " << text_maps[text_maps.size()-1][0] << '\n';
        }
        else if(word == "f") {
            // face detected
            Face *f = new Face();
            inputFile >> *f;
            faces.push_back(f);
        }
        else if(word == "light") { // change this in the future, man it sucks. i dont want to have to differentiate light type
            Vector3 light_pos;
            int type;
            PPMColor light_color;

            inputFile >> light_pos >> type >> light_color;

            if(type == 0) {
                // directonal
                DirectionalLight *d_light = new DirectionalLight();
                d_light->setPosition(light_pos);
                d_light->setColor(light_color);
                d_light->setType(type);

                this->addLight(d_light);
            }
            else if(type == 1) {
                // point
                PointLight *p_light = new PointLight();
                p_light->setPosition(light_pos);
                p_light->setColor(light_color);
                p_light->setType(type);

                this->addLight(p_light);
            }
            else {
                // ERROR
            }
        }
        else if(word == "#") { // comment
            inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            // ERROR
            fprintf(stderr, "Unknown input command: \"%s\"\n", word.c_str());
        }
    }
    inputFile.close();


    // ths converts faces, verticies, texture maps and normals to 

    std::cout << "Faces size: " << faces.size() << "\n";
    if(faces.size() == (verticies.size() - 2)) { 
        for(int i = 0; i < faces.size(); i++) {

            Triangle *tri = new Triangle(); // new instance of triangle to be added to the scene
  
            Vector3 v0 = *(verticies[faces[i]->verticies[0] - 1]);
            Vector3 v1 = *(verticies[faces[i]->verticies[1] - 1]);
            Vector3 v2 = *(verticies[faces[i]->verticies[2] - 1]);

            //std::cout << " did that whooo1\n";

            if(faces[i]->normals[0] != -1 && vertNormals.size() > 0) {
                Vector3 n0 = *(vertNormals[faces[i]->normals[0] - 1]);
                Vector3 n1 = *(vertNormals[faces[i]->normals[1] - 1]);
                Vector3 n2 = *(vertNormals[faces[i]->normals[2] - 1]);
                tri->setNorms(n0, n1, n2);
            }

            if(faces[i]->textures[0] != -1 && text_maps.size() > 0) {

                std::cout << "mapped texture!!!!!!\n";

                int texts[3][2];
                for (int j = 0; j < 3; j++) {
                    texts[j][0] = text_maps[faces[i]->textures[j] - 1][0];
                    texts[j][1] = text_maps[faces[i]->textures[j] - 1][1];
                }
                tri->setTextMaps(texts);
            }

            tri->setVerts(v0, v1, v2);
            tri->setMaterial(current_material);
            this->addObject(tri);

            std::cout << "made trianlge" << *tri << "\n";

        }
    }
    
    std::cout << "Loaded File Successfully\n";
    return;
}

/**
 * @brief returns a value [0-1], 0 if no shadow 1 if direct shadow
 * 
 * @param shape is shape we are calculating the shadow of
 * @param hit is the
 * @param light the light that will cast the shadow
 * @return float 
 */

float Scene::ShadowHit(VisibleObject *shape, Vector3 hit, Light *light) {

    Vector3 L; // a vector between from the hit point to the light source
    Vector3 closest_hit = Vector3::null;

    float closest_dist = INFINITY;
    float curr_dist = closest_dist;
    float dist_to_light = hit.distance(light->getPosition());


    float obj_opacity = 0;
    ObjectHitData light_hit_data;
    VisibleObject *closest_shadow_obj = nullptr;
    Vector3 light_hit;
    Ray ray_light_to_obj;

    for(int i = 0; i < visibleObjects.size(); i++)
    {
        if(visibleObjects[i] == shape)
            continue;

        // directional
        if(light->getType() == 0) {  
            L = (light->getPosition()) * -1; // calculate light vector
            L.normalize();
            ray_light_to_obj = Ray((hit + (L * 0.1)), L);  
        } 
        else if(light->getType() == 1) {
            L = ((light->getPosition() - hit));
            L.normalize();
            ray_light_to_obj = Ray(hit, L);
        }
        else {
            return 1.0;
        }

        if((light_hit = visibleObjects[i]->rayCastHit(ray_light_to_obj, light_hit_data)) != Vector3::null) {
            // it hit an object
            curr_dist = hit.distance(light_hit);

            if(curr_dist < closest_dist) {

                closest_shadow_obj = visibleObjects[i];
                closest_dist = curr_dist;

                obj_opacity += visibleObjects[i]->getMaterial().getOpacity();
            }
        }
    }

    if(closest_dist < 0)
        std::cout << "closest dist: " << closest_dist << '\n';

    if(closest_dist < dist_to_light && closest_shadow_obj->getMaterial().getOpacity() != 0) {
        // hit somethin
        return utility::clampValue(1.0 - obj_opacity);
    }

    return 1.0f;
}


/**
 * @brief 
 * 
 * @param ray 
 * @param shape 
 * @param hit 
 * @param count 
 * @return PPMColor 
 */

PPMColor Scene::ShadeRay(Ray ray, VisibleObject *shape, Vector3 hit, int count) {

    PPMColor color = shape->getMaterial().getColor();

    if(shape->getMaterial().getTexture() != nullptr) {
        float u, v;
        shape->calculateTextureMap(hit, u, v);
        color = shape->getMaterial().getTexture()->getColor(u, v);
    }

    if(lightObjects.size() < 1) return color;  // if no lights return albedo color

    PPMColor ret_color; // define color for return

    float IR = 0, IG = 0, IB = 0;       

    Vector3 N = shape->getSurfaceNormal(hit); // a vector between the point of contact AND the Center of the sphere;
    Vector3 V = (mainCamera->getPosition() - hit); // directon to viewer
    V.normalize();

    Vector3 Weights = shape->getMaterial().getWeight();
     
    PPMColor specular = shape->getMaterial().getSpecular();
    int n = shape->getMaterial().getN();
    
    // set ambient before light calculations
    IR = (Weights.getXValue() * color.getRed());
    IG = (Weights.getXValue() * color.getGreen());
    IB = (Weights.getXValue() * color.getBlue());

    for(int i = 0; i < lightObjects.size(); i++) {

        float shadow_term = ShadowHit(shape, hit, lightObjects[i]);

        Vector3 L;
        Vector3 H;
        PPMColor lightColor;
        float diffuse_reflection;
        float specular_reflection;
        int zero = 1;


        L = lightObjects[i]->getLightVector(hit);
        lightColor = lightObjects[i]->getColor();

        L.normalize();
        
        //H = (L + V);
        H = (L + ray.direction * -1); // TODO check that this works
        H.normalize();

        if(N.dotProduct(L) < 0) {
            zero = 0;
        }

        diffuse_reflection = fmax(0, N.dotProduct(L));
        specular_reflection = pow(fmax(0, N.dotProduct(H)), n);

        IR += shadow_term * lightColor.getRed() * 

        ((Weights.getYValue() * color.getRed() * diffuse_reflection) * zero +
        (Weights.getZValue() * specular.getRed() * specular_reflection));

        IG += shadow_term * lightColor.getGreen() * 
        
        ((Weights.getYValue() * color.getGreen() * diffuse_reflection) * zero +
        (Weights.getZValue() * specular.getGreen() * specular_reflection));
    
        IB += shadow_term * lightColor.getBlue() * 
        
        ((Weights.getYValue() * color.getBlue() * diffuse_reflection) * zero + 
        (Weights.getZValue() * specular.getBlue() * specular_reflection));  
    }

    ret_color.setColor(IR, IG, IB);

    // modify return color with relective properties

    // REFLECTION AND REFRACTION
    /*************************************************/

    PPMColor reflected_color = PPMColor::black;
    PPMColor transp_color = PPMColor::black;

    Vector3 I = ray.direction * -1;

    float Fr = 0;
    bool TIR = false;

    // check to make sure that shape even has specular!
    if(shape->getMaterial().getWeight().getZValue() != 0) {


        float n_t = backgroundMaterial.getRefractionIndex();
        float n_i = shape->getMaterial().getRefractionIndex();

        float angle = N.dotProduct(I);

        Vector3 reflection_dir;

        reflection_dir = (N * angle * 2) - I;
        reflection_dir.normalize();

        Ray reflection_ray = Ray((hit + reflection_dir * 0.01), reflection_dir);

        reflected_color = TraceRay(reflection_ray, count - 1);
        
        if((Fr = calculateFresnel(n_i, n_t, N, I)) == -1) {
            TIR = true;
            Fr = 1.0f;
        }

        reflected_color *= Fr;

    }
    else {
        reflected_color = PPMColor::black; // return zero valued color
    }
    
    
    
    // material is partially transparent
    
    bool exiting = false;
    if(shape->getMaterial().getRefractionIndex() > 0) {

        ObjectHitData refraction_data;

        float n_t;
        float n_i;
        
        Vector3 T;
        Vector3 I = ray.direction;

        I.normalize();
        I = I * -1;

        float angle = N.dotProduct(I); // if angle is negative, it is an interior hit!

        // if angle is negative the ray is exiting the sphere
        if(angle < 0) {  
            exiting = true;
            n_i = shape->getMaterial().getRefractionIndex(); // incoming / is the current refraction inedx
            n_t = backgroundMaterial.getRefractionIndex(); // transmitted / next
    
            N *= -1; // must flip the normal so that it points out
            angle = N.dotProduct(I); // calculate the new angle  
        }
        else {
            // enter!!!
            n_i = backgroundMaterial.getRefractionIndex(); // the current refraction index, incoming
            n_t = shape->getMaterial().getRefractionIndex(); // the objects refraction index, transmitted          
        }

        float ratio = n_i / n_t;

        T = (N * -1) * sqrt(1 - pow(ratio, 2) * (1 - pow(angle, 2))) +  ((N * angle) - I) * ratio;
        T.normalize();

        Ray refraction_ray = Ray(hit+ T * 0.1, T); // refraction_color

        // check for total internal refraction
        if(!TIR) {
            transp_color = TraceRay(refraction_ray, count - 1);

            transp_color *= (1.0 - Fr);
           // transp_color *= pow(M_E, -1.0 * shape->getMaterial().getOpacity() * refraction_data.distance_inside_object);
            transp_color *= (1 - shape->getMaterial().getOpacity());
        }
    }
    else {
        transp_color = PPMColor::black;
    }
    
    
    
    return ret_color + reflected_color + transp_color;
}


/**
 * @brief initiates the tracing of a ray trough the entire scene
 * 
 * @param ray 
 * @param depth 
 * @return PPMColor 
 */

// 'trace' the given ray througought the scene and find the object that it hits first.
// Return the color of that object
PPMColor Scene::TraceRay(Ray ray, int depth) {

    if(depth == 0) return PPMColor::black; // return 0 0 0 when recursion ends

    ObjectHitData hit_data; // store the data from a raycast intersection
    Vector3 closest_hit_point = Vector3::null;
    VisibleObject *closest_object = nullptr;
    float min_dist = INFINITY; // closest distance to hit object found

    for(int l = 0; l < visibleObjects.size(); l++) {

        VisibleObject *obj = visibleObjects[l];

        Vector3 hit_point;
        if((hit_point = obj->rayCastHit(ray, hit_data)) != Vector3::null) {

            float dist_to_hit = mainCamera->getPosition().distance(hit_point); // calculate distance to hit

            if(dist_to_hit < min_dist) {
                // object hit is closer than other object
                closest_object = obj;
                closest_hit_point = hit_point;
                min_dist = dist_to_hit;
            }
        }
    }

    // ray has hit object!
    if(closest_object != nullptr && min_dist != INFINITY) {

        return ShadeRay(ray, closest_object, closest_hit_point, depth);
    }
    return backgroundMaterial.getColor();
}


// Where the magic happens


/**
 * @brief where the magic happens. This is the function that is responsible for rendering everything intially
 * 
 */

void Scene::Render() {
 
    // error, set camera please
    if(mainCamera == nullptr) {
        return;
    }
    
    // Open file for I/O -- should this be its own function?
    std::ofstream outputFile;
    outputFile.open(this->name + ".ppm");
    
    if(!outputFile.is_open()) {
        // error open file
        perror("Could not open output file :(\n");
        exit(1);
    }

    std::cout << "Rendering scene at " << mainCamera->getWidth() << " : " << mainCamera->getHeight() << "\n";

    int width_px = mainCamera->getWidth();
    int height_px = mainCamera->getHeight();
    
    outputFile << "P3 " << width_px << " " << height_px << " 255\n";

    float d = 1;
    float aspect_ratio = (float)width_px / (float)height_px;

    float w, h;

    w = 2.0f * d * tan(((mainCamera->getFOV() / 2.0f) * (M_PI/180.0f))); // find world space heihgt of view window
    h = w / aspect_ratio;

    Vector3 eye_pos, up_dir, view_dir, u, v; // view direction vectors

    eye_pos = mainCamera->getPosition();
    up_dir = mainCamera->getUpDir();
    view_dir = mainCamera->getViewDir();

    //std::cout << "eye pos:" << eye_pos <<'\n';

    Vector3 n = view_dir;

    u = view_dir.crossProduct(up_dir);
    //std::cout << "U: " << u << '\n';
    u.normalize();

    v = u.crossProduct(n);
    v.normalize();

    Vector3 center, distH, distV;
    Vector3 ul, ur, ll, lr;
    Vector3 deltaH, deltaV, deltaCh, deltaCv;

    center = eye_pos + (view_dir * d);

    distH = (u * (w/2.0f));
    distV = (v * (h/2.0f));

    ul = center - distH + distV;
    ur = center + distH + distV;
    ll = center - distH - distV;
    lr = center + distH - distV;

    deltaCh = (ur-ul)/(2.0f * width_px);
    deltaCv = (ll-ul)/(2.0f * height_px);

    deltaH = (ur-ul)/(width_px - 1);
    deltaV = (ll-ul)/(height_px - 1);

    Vector3 current_pixel;
    Vector3 ray_dir;

    Ray ray;


    float total_px = width_px * height_px;
    int percent = 0;
    int last_p = 0;

    // trace ray for every pixel

    std::cout << "Loading: " << std::flush;

    for(int i = 0; i < mainCamera->getHeight(); i++) {
        for(int j = 0; j < mainCamera->getWidth(); j++) {

            current_pixel = ul + (deltaH * j) + (deltaV * i) + deltaCh + deltaCv;
            ray_dir = (current_pixel - eye_pos);

            ray = Ray(eye_pos, ray_dir); // crete a new ray for each pixel

            outputFile << TraceRay(ray, 10); // trace the ray and write resulting color to output file.

            percent += 1;

            int p = int(((float)percent / (float)total_px) * 100);

            

            if (p > last_p){ 
                std::cout << "." << std::flush;

                // if((int)p % 10 == 0) {
                //     std::cout << '\n';
                // }

            }
            
            last_p = p;
        }
    }
    std::cout << " Done!" << '\n';

    outputFile.close(); // close output file once done rendering
    return;
}
