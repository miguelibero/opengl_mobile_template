//
//  Shader.fsh
//  OpenglGame
//
//  Created by mibero on 14/10/14.
//  Copyright (c) 2014 Miguel Ibero. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
