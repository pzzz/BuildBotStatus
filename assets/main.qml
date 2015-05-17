/*
 * main.qml
 *
 *  Created on: 13.05.2015
 *      Author: "Peter Schuller <ps@pzzz.de>"
 */

import bb.cascades 1.4
import bb.system 1.2
import BuildBot.StatusRequest 1.0

NavigationPane {
    id: navPane
    Page {
        id: startView
        ScrollView {
            scrollViewProperties.scrollMode: ScrollMode.Vertical
            scrollViewProperties.pinchToZoomEnabled: false
            Container {
                topPadding: ui.du(2.0)
                leftPadding: ui.du(2.0)
                rightPadding: ui.du(2.0)
                
                Label {
                    text: "URL of BuildBot Server"
                
                }
                TextField {
                    id: buildbot_url
                    text: "buildbot.buildbot.net"
                    //Sets the default server to Buildbot's Buildbot to provide an instant example
                
                }
                Label {
                    text: "Enable HTTPS"
                
                }
                ToggleButton {
                    id: enableHTTPS
                    checked: false
                
                }
                Label {
                    text: "Enable HTTP Basic Auth"
                
                }
                ToggleButton {
                    id: enableBasicAuth
                    onCheckedChanged: {
                        lblBasicAuthUser.enabled = ! lblBasicAuthUser.enabled;
                        basicAuthUser.enabled = ! basicAuthUser.enabled;
                        lblBasicAuthPass.enabled = ! lblBasicAuthPass.enabled;
                        basicAuthPass.enabled = ! basicAuthPass.enabled;
                    }
                
                }
                Label {
                    id: lblBasicAuthUser
                    text: "Username"
                    enabled: false
                
                }
                TextField {
                    id: basicAuthUser
                    enabled: false
                
                }
                Label {
                    id: lblBasicAuthPass
                    enabled: false
                    text: "Password"
                
                }
                TextField {
                    id: basicAuthPass
                    enabled: false
                
                }
                Button {
                    id: connectBtn
                    text: "Connect"
                    
                    horizontalAlignment: HorizontalAlignment.Center
                    
                    onClicked: {
                        _buildbotstatus.buildBotUrl = buildbot_url.text;
                        _buildbotstatus.useHttps = enableHTTPS.checked;
                        _buildbotstatus.useHttpBasicAuth = enableBasicAuth.checked;
                        if (enableBasicAuth.checked) {
                            _buildbotstatus.basicAuthUser = basicAuthUser.text;
                            _buildbotstatus.basicAuthPass = basicAuthPass.text;
                        }
                        navPane.insert(2, statusPage);
                        statreq.getBuilders(_buildbotstatus.buildBotUrl, _buildbotstatus.useHttps, _buildbotstatus.useHttpBasicAuth, _buildbotstatus.basicAuthUser, _buildbotstatus.basicAuthPass);
                    }
                }
            }
        }
    }

    attachedObjects: [
        Page {
            id: statusPage
            Container {
                topPadding: ui.du(2.0)
                leftPadding: ui.du(2.0)
                rightPadding: ui.du(2.0)

                ListView {
                    dataModel: ArrayDataModel {
                        id: builds

                    }
                }

                attachedObjects: [
                    StatusRequest {
                        id: statreq
                        onComplete: {
                            builds.append(value);
                        }
                        onError: {
                            toast.body = "Error: " + error
                            toast.show();
                        }
                    }
                ]
            }
        },
        
        SystemToast {
            id: toast
        }
    ]
    
    onPopTransitionEnded: { builds.clear() }
}