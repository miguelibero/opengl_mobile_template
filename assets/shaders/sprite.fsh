
uniform sampler2D texture;

void main()
{
    gl_FragColor = texture(texture, gl_Position);
}
