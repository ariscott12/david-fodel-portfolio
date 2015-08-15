module.exports = function(grunt) {
    //  require('matchdep').filterDev('grunt-*').forEach(grunt.loadNpmTasks);
    grunt.initConfig({

        sass: {
            dist: {

                files: {
                    "css/main.css": "sass/main.scss",
                },
                options: { // Target options
                    includePaths: require("node-bourbon").includePaths,
                    style: "compact"

                }
            }
        },
        watch: {
            sass: {
                files: [
                    "sass/*.scss"
                ],
                tasks: "sass"
            },
        }
    });

    //Where we tell Grunt we plan to use this plug-in.
    grunt.loadNpmTasks("grunt-contrib-watch");
    grunt.loadNpmTasks("grunt-sass");
  
    //Where we tell Grunt what to do when we type "grunt" into the terminal.
    grunt.registerTask("default", ["watch"]);



};