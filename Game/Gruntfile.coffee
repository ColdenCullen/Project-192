module.exports = ( grunt ) ->

    scriptFiles = './Assets/Scripts/**/*.ts'
    assetFiles = [ './Assets/Textures/**', './Assets/Meshes/**' ]
    shaderFiles = './Shaders/**'
    configFiles = './Config/**'
    objectFiles = './Objects/**'
    uiFiles = './UIs/**'
    autos = [ './Assets/Scripts/*.js', './Gruntfile*.js' ]

    interDest = './.bin/'

    grunt.initConfig
        pkg: grunt.file.readJSON( 'package.json' )
        watch:
            scripts:
                files: scriptFiles
                tasks: [ 'typescript:game', 'copy:output', 'clean:autocompiled' ]
            assets:
                files: assetFiles
                tasks: [ 'copy:assets', 'copy:output', 'clean:autocompiled' ]
            shaders:
                files: shaderFiles
                tasks: [ 'copy:shaders', 'copy:output', 'clean:autocompiled' ]
            config:
                files: configFiles
                tasks: [ 'copy:config', 'copy:output', 'clean:autocompiled' ]
            uis:
                files: uiFiles
                tasks: [ 'copy:uis', 'copy:output', 'clean:autocompiled' ]
            objects:
                files: objectFiles
                tasks: [ 'copy:objects', 'copy:output', 'clean:autocompiled' ]
            autos:
            	files: autos
            	tasks: [ 'clean:autocompiled' ]

        typescript:
            game:
                src: scriptFiles
                dest: interDest + 'Scripts/output.js'
                options:
                    module: 'amd'
                    target: 'es5'
                    base_path: './Scripts'
                    sourcemap: true
                    fullSourceMapPath: true

        copy:
            assets:
                files: [
                    expand: true
                    src: assetFiles
                    dest: interDest
                ]
            shaders:
                files: [
                    expand: true
                    src: shaderFiles
                    dest: interDest
                ]
            config:
                files: [
                    expand: true
                    src: configFiles
                    dest: interDest
                ]
            uis:
                files: [
                    expand: true
                    src: uiFiles
                    dest: interDest
                ]
            objects:
                files: [
                    expand: true
                    src: objectFiles
                    dest: interDest
                ]
            output:
                files: [
                    expand: true
                    cwd: interDest
                    src: '**'
                    dest: '<%= outputdir %>/Resources'
                ]
                
        clean:
            output:
                src: interDest
            autocompiled:
                src: autos

        config: grunt.option( 'config' ) || 'debug'
        outputdir: './../Output/Final/<%= config %>'

    grunt.registerTask 'build', [ 'typescript:game', 'copy', 'clean:autocompiled' ]

    grunt.registerTask 'default', 'build'

    grunt.loadNpmTasks 'grunt-typescript'
    grunt.loadNpmTasks 'grunt-contrib-copy'
    grunt.loadNpmTasks 'grunt-contrib-clean'
    grunt.loadNpmTasks 'grunt-contrib-watch'
