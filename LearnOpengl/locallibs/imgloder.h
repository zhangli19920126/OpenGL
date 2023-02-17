#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image.h"

class ImgLoader
{
public:

	//���غ�ͼ��Ŀ�ȡ��߶Ⱥ���ɫͨ���ĸ�����ֱ���䵽wid��hei��channels��3������
	void loadImg(const char* filename, int* wid, int* hei, int* channels, int req_channel)
	{
		unsigned char* data = stbi_load(filename, wid, hei, channels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, *wid, *hei, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
	}

    //��ǰ�󶨵�����texture�� x�ỷ�Ʒ�ʽs_wrap_value��y�ỷ�Ʒ�ʽt_wrap_value��
    //ͼƬ����ʱ���˷�ʽmin_filter_value��ͼƬ̫Сʱ���˷�ʽmax_filter_value
    void bindTexture(unsigned int* texture, int s_wrap_value, int t_wrap_value, int min_filter_value, int max_filter_value)
    {
        glGenTextures(1, texture);
        glBindTexture(GL_TEXTURE_2D, *texture); 
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s_wrap_value);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t_wrap_value);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter_value);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, max_filter_value);
    }

private:

};



