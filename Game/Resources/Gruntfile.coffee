module.exports = ( grunt ) ->

    scriptFiles = './Scripts/**/*.ts'
    assetFiles = './Assets/**'
    shaderFiles = './Shaders/**'
    configFiles = './Config/**'
    uiFiles = './UIs/**'

    interDest = './bin/'

    grunt.initConfig
        pkg: grunt.file.readJSON( 'package.json' )
        watch:
            scripts:
                files: scriptFiles
                tasks: [ 'typescript:game', 'copy:output' ]
            assets:
                files: assetFiles
                tasks: [ 'copy:assets', 'copy:output' ]
            shaders:
                files: shaderFiles
                tasks: [ 'copy:shaders', 'copy:output' ]
            config:
                files: configFiles
                tasks: [ 'copy:config', 'copy:output' ]
            uis:
                files: uiFiles
                tasks: [ 'copy:uis', 'copy:output' ]
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
            output:
                files: [
                    expand: true
                    cwd: interDest
                    src: '**'
                    dest: '<%= outputdir %>/Resources'
                ]
        clean:
            output:
                src: [ interDest ]

        config: grunt.option( 'config' ) || 'debug'
        outputdir: './../../Output/Final/<%= config %>'

    grunt.registerTask 'build', [ 'typescript:game', 'copy' ]

    grunt.registerTask 'default', 'build'

    grunt.loadNpmTasks 'grunt-typescript'
    grunt.loadNpmTasks 'grunt-contrib-copy'
    grunt.loadNpmTasks 'grunt-contrib-clean'
    grunt.loadNpmTasks 'grunt-contrib-watch'
