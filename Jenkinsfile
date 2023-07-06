node {
    def realpath = sh(script: """
        docker inspect jenkins --format='{{range .Mounts}}{{if eq .Destination "/var/jenkins_home"}}{{.Source}}{{end}}{{end}}'
    """, returnStdout: true).trim()
    echo "realPath:" + realpath

    def realWorkspace = env.WORKSPACE
    echo "realworkspace:" + realWorkspace

    def workspaceRealDir= realWorkspace.replace("/var/jenkins_home",realpath)
    echo "workspaceRealDir:" + workspaceRealDir

    stage('Clone sources') {
          checkout scm
    }
    stage('Build') {
        withEnv(["PROJECT_DIR=${workspaceRealDir}"]){
            sh('docker run --rm -v "${PROJECT_DIR}":/work axemsolutions/make_gnu_arm /bin/sh -c "make"')
        }
    }
    stage('Test') {
        withEnv(["PROJECT_DIR=${workspaceRealDir}"]){
            sh('docker run --rm -v "${PROJECT_DIR}":/work axemsolutions/cpputest /bin/sh -c "cd app/test; make"')
        }
    }
}
