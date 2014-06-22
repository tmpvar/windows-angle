#include "ANGLETest.h"

class BlendMinMaxTest : public ANGLETest
{
protected:
    BlendMinMaxTest()
    {
        setWindowWidth(128);
        setWindowHeight(128);
        setConfigRedBits(8);
        setConfigGreenBits(8);
        setConfigBlueBits(8);
        setConfigAlphaBits(8);
        setConfigDepthBits(24);

        mProgram = 0;
        mColorLocation = -1;
    }

    struct Color
    {
        float values[4];
    };

    static GLubyte getExpected(bool blendMin, float curColor, GLubyte prevColor)
    {
        GLubyte curAsUbyte = (curColor * std::numeric_limits<GLubyte>::max()) + 0.5f;
        return blendMin ? std::min<GLubyte>(curAsUbyte, prevColor) : std::max<GLubyte>(curAsUbyte, prevColor);
    }

    void runTest()
    {
        const size_t colorCount = 1024;
        Color colors[colorCount];
        for (size_t i = 0; i < colorCount; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                colors[i].values[j] = (rand() % 255) / 255.0f;
            }
        }

        GLubyte prevColor[4];
        for (size_t i = 0; i < colorCount; i++)
        {
            const Color &color = colors[i];
            glUseProgram(mProgram);
            glUniform4f(mColorLocation, color.values[0], color.values[1], color.values[2], color.values[3]);

            bool blendMin = (rand() % 2 == 0);
            glBlendEquation(blendMin ? GL_MIN : GL_MAX);

            drawQuad(mProgram, "aPosition", 0.5f);

            if (i > 0)
            {
                EXPECT_PIXEL_EQ(0, 0,
                                getExpected(blendMin, color.values[0], prevColor[0]),
                                getExpected(blendMin, color.values[1], prevColor[1]),
                                getExpected(blendMin, color.values[2], prevColor[2]),
                                getExpected(blendMin, color.values[3], prevColor[3]));
            }

            glReadPixels(0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, prevColor);
        }
    }

    virtual void SetUp()
    {
        ANGLETest::SetUp();

        const std::string testVertexShaderSource = SHADER_SOURCE
        (
            attribute highp vec4 aPosition;

            void main(void)
            {
                gl_Position = aPosition;
            }
        );

        const std::string testFragmentShaderSource = SHADER_SOURCE
        (
            uniform highp vec4 color;
            void main(void)
            {
                gl_FragColor = color;
            }
        );

        mProgram = compileProgram(testVertexShaderSource, testFragmentShaderSource);
        if (mProgram == 0)
        {
            FAIL() << "shader compilation failed.";
        }

        mColorLocation = glGetUniformLocation(mProgram, "color");

        glUseProgram(mProgram);

        glClearColor(0, 0, 0, 0);
        glClearDepthf(0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_BLEND);
        glDisable(GL_DEPTH_TEST);
    }

    void SetUpFramebuffer(GLenum colorFormat)
    {
        glGenFramebuffers(1, &mFramebuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mFramebuffer);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, mFramebuffer);

        glGenRenderbuffers(1, &mColorRenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, mColorRenderbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, colorFormat, getWindowWidth(), getWindowHeight());
        glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, mColorRenderbuffer);

        ASSERT_GL_NO_ERROR();
    }

    virtual void TearDown()
    {
        glDeleteProgram(mProgram);
        glDeleteFramebuffers(1, &mFramebuffer);
        glDeleteRenderbuffers(1, &mColorRenderbuffer);

        ANGLETest::TearDown();
    }

    GLuint mProgram;
    GLint mColorLocation;

    GLuint mFramebuffer;
    GLuint mColorRenderbuffer;
};

TEST_F(BlendMinMaxTest, rgba8)
{
    SetUpFramebuffer(GL_RGBA8);
    runTest();
}

TEST_F(BlendMinMaxTest, rgba32f)
{
    SetUpFramebuffer(GL_RGBA32F);
    runTest();
}

TEST_F(BlendMinMaxTest, rgba16f)
{
    SetUpFramebuffer(GL_RGBA16F);
    runTest();
}
