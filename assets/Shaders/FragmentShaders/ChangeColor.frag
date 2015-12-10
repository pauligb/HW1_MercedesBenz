#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D texture;
uniform sampler2D mainColorMask;
uniform vec4 colorToPaint;
varying vec2 v_texcoord;

void main()
{
    vec4 mask = texture2D(mainColorMask, v_texcoord);
    if(mask.r > 0.5)
    {
        gl_FragColor = texture2D(texture, v_texcoord);
    }
    else
    {
        gl_FragColor = colorToPaint;
    }
}
