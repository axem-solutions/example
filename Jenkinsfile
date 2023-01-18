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
            sh('ls -la')
            sh('./axem/BUILD/build.sh')
        }
    }
    stage('Test') {
        withEnv(["PROJECT_DIR=${workspaceRealDir}"]){        
            sh('./axem/TEST/unit_test.sh')
        }
    }
}
