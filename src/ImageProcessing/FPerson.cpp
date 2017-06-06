//
// Created by Danil Kazimirov on 05.06.17.
//

#include <FPerson.h>
#include <Facecope.h>
#include <FFaceArea.h>
#include <Utils.h>
#include <iostream>

using namespace std;
using namespace cv;

FPerson::FPerson(FFaceArea &parent, Rect &eye_frame_1, Rect &eye_frame_2, long id) {
    this->parent = &parent;
    set_eyes(eye_frame_1, eye_frame_2);
    set_ID(id);
    this->normilized = false;
}

FPerson::~FPerson() {
    cout << "person deleted" << endl;
}

FFaceArea *FPerson::getParent() {
    return parent;
}

Eye FPerson::get_eye_left() {
    normalize();
    Point rotatedP(eye_left.pos.x-frame.x,eye_left.pos.y-frame.y);
    Point center(parent->size().width / 2, parent->size().height / 2);
    rotatePoint(rotatedP, center, -toRadians(rotation_degree));
    return Eye{.pos=rotatedP, eye_left.radius};
}

Eye FPerson::get_eye_rigth() {
    normalize();
    Point rotatedP(eye_rigth.pos.x-frame.x,eye_rigth.pos.y-frame.y);
    Point center(parent->size().width / 2, parent->size().height / 2);
    rotatePoint(rotatedP, center, -toRadians(rotation_degree));
    return Eye{.pos=rotatedP, eye_rigth.radius};
}

long FPerson::get_ID() {
    return ID;
}

void FPerson::set_ID(long id) {
    this->ID = id;
}

Mat FPerson::get_image() {
    normalize();
    cout << rotation_degree << endl;
    Mat p = parent->get_image();
    Mat r = rotate(p, rotation_degree);
    p.release();
    return r(frame);
}

void FPerson::normalize() {
    if (!normilized) {
        //todo
        this->rotation_degree = toDegrees(getAngle_radians(eye_left.pos, eye_rigth.pos));
        cout << rotation_degree << " Rotation" << endl;
        if (rotation_degree > 15) {
            rotation_degree = 15;
        } else if (rotation_degree < -15) {
            rotation_degree = -15;
        }
        //randomize rotation to debug
//        rotation_degree = -15 + rand() % 30;
        normilized = true;
        auto _e1 = get_eye_left();
        auto _e2 = get_eye_rigth();
        this->frame.x = max(_e1.pos.x - _e1.radius * 2, 0);
        this->frame.y = max(min(_e1.pos.y - _e1.radius * 2, _e2.pos.y - _e2.radius * 2), 0);
        this->frame.width = min(_e2.pos.x + _e2.radius * 2 - frame.x, parent->size().width - frame.x);
        this->frame.height = parent->size().height - frame.y;
    }
}

bool isValidEye(Rect &eye_frame) {
    return eye_frame.x >= 0 && eye_frame.y >= 0 && eye_frame.height > 0 && eye_frame.width > 0;
}

void FPerson::create_eyes(Rect &eye_frame) {
    Size s = parent->size();
    Eye eye = createEye(eye_frame);

    if (eye.pos.x > s.width >> 1) {
        //if it rigth eye
        this->eye_rigth = eye;
        this->eye_left = getPair(eye, Rect(0, 0, s.width, s.height));
    } else {
        //if it left eye
        this->eye_left = eye;
        this->eye_rigth = getPair(eye, Rect(0, 0, s.width, s.height));
    }
}

void FPerson::set_eyes(cv::Rect &eye_frame_1, cv::Rect &eye_frame_2) {
    bool valid_1 = isValidEye(eye_frame_1);
    bool valid_2 = isValidEye(eye_frame_2);
    if (valid_1 && valid_2) {
        //if two eye is valid
        Size s = parent->size();
        Eye eye = createEye(eye_frame_1);
        if (eye.pos.x < s.width / 2) {
            eye_left = eye;
            eye_rigth = createEye(eye_frame_2);
        } else {
            eye_rigth = eye;
            eye_left = createEye(eye_frame_2);
        }
        cout << "2 valid eye" << endl;
    } else if (valid_1) {
        create_eyes(eye_frame_1);
        cout << "left valid eye" << endl;
    } else if (valid_2) {
        create_eyes(eye_frame_2);
        cout << "rigth valid eye" << endl;
    } else {
        Size s = parent->size();
        //if two eye is invalid
        //predict them
        eye_left = Eye{.pos=Point(s.width / 4, s.height / 3), .radius=s.height / 6};
        eye_rigth = Eye{.pos=Point(s.width / 4 * 3, s.height / 3), .radius=s.height / 6};
    }
    if (eye_rigth.radius < 3) {
        eye_rigth.radius = 3;
    }
    if (eye_left.radius < 3) {
        eye_left.radius = 3;
    }
    normilized = false;
}